#include "emufs.h"

/**************************** File system helper functions ****************************/


time_t tim;
//	Function to encrypt a block of data 
int encrypt(char* input, char* encrypted)
{
	for(int i=0; i<BLOCKSIZE; i++)
	{
		encrypted[i] = ~input[i];
	}
}

//	Function to decrypt a block of data 
int decrypt(char* input, char* decrypted)
{
	for(int i=0; i<BLOCKSIZE; i++)
	{
		decrypted[i] = ~input[i];
	}
}

//	The following helper functions are used to read and write 
//	superblock and metadata block. 
//	Change the function definitions with required arguments
struct superblock_t* readSuperblock(struct mount_t *mp)
{
	// struct mount_t *mp;
	// mp = opendevice(name,42);
	char buf[BLOCKSIZE];
	readblock(mp->device_fd,0,buf);
	// printf("%s\n",buf);
	struct superblock_t* superblock;
	superblock = (struct superblock_t*)malloc(sizeof(struct superblock_t));
	memcpy(superblock, buf, sizeof(struct superblock_t));
	return superblock;

	/*
		* Read 0th block from the device into a blocksize buffer
		* Create superblock_t variable and fill it using reader buffer
		* Return the superblock_t variable
	*/
}

int writeSuperblock(struct mount_t* mp,struct superblock_t* superblock)
{
	char buf[BLOCKSIZE];
	readblock(mp->device_fd,0,buf);
	memcpy(buf,superblock, sizeof(struct superblock_t));
	return writeblock(mp->device_fd,0,buf);

	/*
		* Read the 0th block from device into a buffer
		* Write the superblock into the buffer
		* Write back the buffer into block 0
	*/
}

struct metadata_t* readMetadata(struct mount_t *mp)
{
	char buf[BLOCKSIZE];
	readblock(mp->device_fd,1,buf);
	struct metadata_t* md;
	// printf("%s\n",buf );
	md=(struct metadata_t*)malloc(sizeof(struct metadata_t));
	if(mp->fs_number==1)
	{
		decrypt(buf,buf);
	}
	memcpy(md, buf, sizeof(struct metadata_t));
	return md;
	// Same as readSuperblock(), but it is stored on block 1
	// Need to decrypt if emufs-encrypted is used  
}

int writeMetadata(struct mount_t* mp,struct metadata_t* md)
{
	char buf[BLOCKSIZE];
	memcpy(buf, md, sizeof(struct metadata_t));
	// md=(struct metadata_t*)malloc(sizeof(struct metadata_t));
	if(mp->fs_number==1)
	{
		encrypt(buf,buf);
	}
	return writeblock(mp->device_fd,1,buf);
	// Same as writeSuperblock(), but it is stored on block 1
	// Need to decrypt/encrypt if emufs-encrypted is used  
}

/**************************** File system API ****************************/

int create_file_system(struct mount_t *mount_point, int fs_number)
{
	/*
	   	* Read the superblock.
	    * Set file system number on superblock
		* Clear the bitmaps.  values on the bitmap will be either '0', or '1', or'x'. 
		* Create metadata block in disk
		* Write superblock and metadata block back to disk.

		* Return value: -1,		error
						 1, 	success
	*/
	struct superblock_t* sb=readSuperblock(mount_point);
	sb->fs_number=fs_number;
	mount_point->fs_number=fs_number;
	for(int i=2;i<sb->disk_size;i++)
	{
		sb->bitmap[i]='0';
	}
	for(int i=sb->disk_size;i<MAX_BLOCKS;i++)
		sb->bitmap[i]= 'x';
	struct metadata_t* md;
	md=(struct metadata_t*)malloc(sizeof(struct metadata_t));
	for(int i=0;i<MAX_FILES;i++)
	{
		md->inodes[i].status=0;
		md->inodes[i].modtime=time(NULL);
		for(int j=0;j<4;j++)
		{
			md->inodes[i].blocks[j]=-1;
		}

	}
	if(writeSuperblock(mount_point,sb)<0) {
		sb->bitmap[0]='1';
		return -1;
	}
	int x= writeMetadata(mount_point,md);
	sb->bitmap[1]='1';
	return x;

}


struct file_t* eopen(struct mount_t* mount_point, char* filename)
{
	/* 
		* If file exist, get the inode number. inode number is the index of inode in the metadata.
		* If file does not exist, 
			* find free inode.
			* allocate the free inode as USED
			* if free id not found, print the error and return -1
		* Create the file hander (struct file_t)
		* Initialize offset in the file hander
		* Return file handler.

		* Return NULL on error.
	*/
	struct metadata_t *md=readMetadata(mount_point);
	int inode=-1;
	for(int i=0;i<MAX_FILES;i++)
	{
		if(md->inodes[i].status==1 && strcmp(filename,md->inodes[i].name)==0)
		{
			inode=i;
			break;
		}			
	}
	if(inode==-1){
		for(int i=0;i<MAX_FILES;i++)
		{
			if(md->inodes[i].status==0){
				md->inodes[i].status=1;
				inode=i;
				strcpy(md->inodes[i].name,filename);
				md->inodes[i].file_size=0;
				for(int j=0;j<4;j++)
					md->inodes[i].blocks[j]=-1;
				md->inodes[i].modtime=time(NULL);
				int w=writeMetadata(mount_point,md);
				if(w<0)
				{
					printf("File could not be created\n");
				}
				break;
			}
		}
	}
	struct file_t* file;
	file= (struct file_t*)malloc(sizeof(struct file_t));
	if(inode==-1)
	{
		printf("Error: File not found. Not enough space on disk to create new file.\n");
		return NULL;
	}
	else{
		file->inode_number=inode;
		// printf("file:%d\n",inode );
		file->mount_point=mount_point;
		// printf("%s\n",mount_point->device_name );
		file->offset=0;
		printf("File '%s' Opened\n", filename);
		return file;		
	}
	
	
}

int ewrite(struct file_t* file, char* data, int size)
{
	// You do not need to implement partial writes in case file exceeds 4 blocks
	// or no free block is available in the disk. 

	// Return value: 	-1,  error
	//					Number of bytes written
	int off=file->offset;
	if(off+size>2048)
	{
		printf("ERROR: Maximum File Size Exceeded\n");
		return -1;
	}
	struct metadata_t* md=readMetadata(file->mount_point);
	struct inode_t inode=md->inodes[file->inode_number];
	struct mount_t* mp=file->mount_point;
	struct superblock_t* sb=readSuperblock(mp);
	// char *buf;
	// buf=(char*)malloc(BLOCKSIZE*sizeof(char));
	int j=0,block=-1,bytes=0;
	sb->bitmap[sb->disk_size-1]='0';
	for(int i=off/BLOCKSIZE;i<(off+size)/BLOCKSIZE;i++)
	{
		// buf=&data[(i*BLOCKSIZE)-off];
		if(sb->fs_number==1)
			encrypt(data+i*BLOCKSIZE-off,data+i*BLOCKSIZE-off);
		if(inode.blocks[i]==-1)
		{
			for(j=0;j<MAX_BLOCKS;j++)
			{
				if(sb->bitmap[j]-'0'==0) {
					block=j;
					break;
				}
			}
			if(block==-1)
			{
				printf("ERROR: Out of diskspace\n");
				return -1;
			}
			if(writeblock(mp->device_fd,block,data+i*BLOCKSIZE-off));
			{
				inode.file_size+=BLOCKSIZE;
				// printf("Written: %d\n",block);
				sb->bitmap[block]='1';
				int w=writeSuperblock(mp,sb);
				inode.blocks[i]=block;
				inode.modtime=time(NULL);
				bytes+=BLOCKSIZE;
				file->offset+=BLOCKSIZE;
			}
			block=-1;
		}
		else{
			block=inode.blocks[i];
			if(writeblock(mp->device_fd,block,data+i*BLOCKSIZE-off));
			{
				// printf("Written2\n");
				// inode.file_size+=BLOCKSIZE;
				// inode.blocks[i]=block;
				// sb->bitmap[block]='1';
				inode.modtime=time(NULL);
				bytes+=BLOCKSIZE;
				file->offset+=BLOCKSIZE;
			}
		}
	}
	md->inodes[file->inode_number]=inode;
	int w=writeMetadata(mp,md);
	if(w<0) printf("Error in writing file\n");
	return bytes;
}

int eread(struct file_t* file, char* data, int size)
{
	// NO partial READS.

	// Return value: 	-1,  error
	//					Number of bytes read
	// printf("Hello\n");
	int off=file->offset;
	struct metadata_t* md=readMetadata(file->mount_point);
	if(off+size > md->inodes[file->inode_number].file_size)
		return -1;
	
	struct inode_t inode=md->inodes[file->inode_number];
	struct mount_t* mp=file->mount_point;
	struct superblock_t* sb=readSuperblock(mp);
	// char *buf;
	// buf=(char*)malloc(BLOCKSIZE*sizeof(char));
	int bytes=0;
	for(int i=off/BLOCKSIZE;i<(off+size)/BLOCKSIZE;i++)
	{
		// buf=&data[(i*BLOCKSIZE)-off];
		int j=inode.blocks[i];
		if(j<0) {
			printf("Cannot read\n");
			return bytes;
		}
		else{
			if(readblock(mp->device_fd,j,data+i*BLOCKSIZE-off)) {
				bytes+=BLOCKSIZE;
				file->offset+=BLOCKSIZE;
				if(sb->fs_number==1)
					decrypt(data+i*BLOCKSIZE-off,data+i*BLOCKSIZE-off);
			}
		}

	}
	// printf("Bye\n");
	return bytes;
}

void eclose(struct file_t* file)
{	
	free(file);
	printf("File Closed\n");
	// free the memory allocated for the file handler 'file'
}

int eseek(struct file_t *file, int offset)
{
	// Change the offset in file hanlder 'file'
	file->offset=offset;
	return 1;
}

void fsdump(struct mount_t* mount_point)
{
	printf("\n[%s] fsdump \n", mount_point->device_name);
	printf("%-10s %6s \t[%6s] \t%s\n", "  NAME", "SIZE", "BLOCKS", "LAST MODIFIED");
	struct metadata_t *md=readMetadata(mount_point);
	for(int i=0;i<MAX_FILES;i++)
	{
		if(md->inodes[i].status==1)
		{
			printf("%-10s %6d \t[%d %d %d %d] \t%s", 
				md->inodes[i].name, 
				md->inodes[i].file_size,
				md->inodes[i].blocks[0],
				md->inodes[i].blocks[1],
				md->inodes[i].blocks[2],
				md->inodes[i].blocks[3],
				asctime(localtime(&(md->inodes[i].modtime))));
		}
	}	

}
