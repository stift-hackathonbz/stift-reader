stty -F /dev/ttyACM0 115200



while true
do 
INOUT=""
read INOUT < /dev/ttyACM0
if test -z "$INOUT" 
then
      sleep 1
else
  if [ ${#INOUT} -ge 2 ]; then
      INOUT=${INOUT::-2}
      echo "$INOUT"	
      curl -X POST "https://stift-server.herokuapp.com/api/rfid/$INOUT"	
  fi
fi
done
