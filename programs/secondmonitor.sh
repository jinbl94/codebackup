#! /bin/bash -

IN="eDP1"
EXT="HDMI1"

if (xrandr | grep "$EXT" | grep "+")
    then
    xrandr --output $EXT --off --output $IN --auto
    else
        if (xrandr | grep "$EXT" | grep " connected")
            then
			xrandr --output HDMI1 --same-as eDP1 --auto
        fi
fi
exit
