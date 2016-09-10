@@name 从光盘提取iso

dd if=/dev/cdrom of=/media/happy/新加卷/NHCEII_RW2.iso

@@end

@@name dd速度查看

每5秒输出dd的进度

watch -n 5 pkill -USR1 ^dd$

watch -n 5 killall -USR1 dd

while killall -USR1 dd; do sleep 5; done

while (ps auxww |grep " dd " |grep -v grep |awk '{print $2}' |while read pid; do kill -USR1 $pid; done) ; do sleep 5; done

@@end
