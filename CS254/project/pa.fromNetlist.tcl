
# PlanAhead Launch Script for Post-Synthesis floorplanning, created by Project Navigator

create_project -name fpgalink -dir "/home/nikhilsamrat/fpgalink/planAhead_run_2" -part xc6slx45csg324-3
set_property design_mode GateLvl [get_property srcset [current_run -impl]]
set_property edif_top_file "/home/nikhilsamrat/fpgalink/top_level.ngc" [ get_property srcset [ current_run ] ]
add_files -norecurse { {/home/nikhilsamrat/fpgalink} {ipcore_dir} }
add_files [list {ipcore_dir/fifo.ncf}] -fileset [get_property constrset [current_run]]
set_property target_constrs_file "board.ucf" [current_fileset -constrset]
add_files [list {board.ucf}] -fileset [get_property constrset [current_run]]
link_design
