# movie.tcl

# A Vis5d Tcl script for saving a whole time series of images

# You may need to change these:
set base "frame"
#set ext ".gif"
#set format VIS5D_GIF
set ext ".ppm.gz"
set format VIS5D_PPMGZ

set numtimes [ vis5d_get_dtx_numtimes $ctx ]

# currently redo color map by hand (and turn on clipping)
vis5d_enable_graphics $ctx VIS5D_VOLUME 0 VIS5D_ON
vis5d_graphics_mode $ctx VIS5D_BOX VIS5D_ON
vis5d_graphics_mode $ctx VIS5D_CLOCK VIS5D_ON
vis5d_set_logo_size $ctx 10000

# starts from right
        #vis5d_set_vclip $ctx 0 0 32 32 32
# starts from left
        #vis5d_set_vclip $ctx 1 0 32 32 32
# starts from left
        #vis5d_set_vclip $ctx 2 0 32 32 32
# starts from right
        #vis5d_set_vclip $ctx 3 0 32 32 32

        # standard good view
        #vis5d_set_view $ctx -15 0 0 1 0 0 0
        #vis5d_set_vclip $ctx 1 32 0 32 32
set rot [expr (0)]
set clip1 [expr (0)]
set clip2 [expr (0)]
puts "Hello World!"

set restart 0
if {$restart==1} {
# if failed after 400, use below
    set time 99
    set rot [ expr ($time/99.0*(-15.0)) ]
    vis5d_set_view $ctx $rot 0 0 1 0 0 0
    set time 199
    set clip1 [ expr (64-($time-100.0)/99.0*(32.0)) ]
    vis5d_set_vclip $ctx 2 $clip1 0 $clip1 32
    set tstart 1025
} else {
#normal start
set tstart 0
}


for {set time $tstart} {$time<$numtimes} {set time [expr $time+1]} {
# clip uses absolute ref, and # is different edge from which clipped
    if {$time<100.0} {
	set rot [ expr ($time/99.0*(-15.0)) ]
	vis5d_set_view $ctx $rot 0 0 1 0 0 0
    } elseif {$time<200.0} {
	set clip1 [ expr (64-($time-100.0)/99.0*(32.0)) ]
	vis5d_set_vclip $ctx 2 $clip1 0 $clip1 32
    } elseif  {$time<300.0} {
	set clip2 [ expr (64-($time-200.0)/99.0*(32.0)) ]
        vis5d_set_hclip $ctx 0 $clip2
    } elseif  {$time<400.0} {
	set clip2 [ expr (32+($time-300.0)/99.0*(32.0)) ]
        vis5d_set_hclip $ctx 0 $clip2
    }
    puts "time $time"
    puts "rot $rot"
    puts "clip1 $clip1"
    puts "clip2 $clip2"

    vis5d_set_dtx_timestep $ctx $time
    vis5d_draw_frame $ctx
    if {$time<10.0} {
        set middle 000
    } elseif {$time<100.0} {
        set middle 00
    } elseif {$time<1000.0} {
        set middle 0
    } else {
	set middle ""
    }
    set name $base$middle$time$ext
    
    vis5d_save_window $name $format
}


# At this point you may want to invoke a Unix utility to convert a
# series of GIF files into an MPEG animation file.....
