#! /bin/bash -

export SteamAppId=322330                                                         
export SteamGameId=322330

if which xterm; then
        XTERM="xterm"
elif [ -f /usr/bin/xterm ]; then
        XTERM="/usr/bin/xterm"
else
        echo "Error launching dedicated server: Cannot locate xterm."
        exit 1
fi

cd /home/tang/.local/share/Steam/steamapps/common/Don\'t\ Starve\ Together\ Dedicated\ Server/bin/

"$XTERM" -e ./dontstarve_dedicated_server_nullrenderer -console -cluster myserver -shard Master &

"$XTERM" -e ./dontstarve_dedicated_server_nullrenderer -console -cluster myserver -shard Caves &

