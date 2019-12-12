sudo cgcreate -g cpu:/cpulimit
sudo cgset -r cpu.cfs_period_us=1000000 cpulimit
sudo cgset -r cpu.cfs_quota_us=100000 cpulimit

sudo cgcreate -g memory:/memorylimit
sudo cgset -r memory.limit_in_bytes=2000000 memorylimit
sudo cgset -r memory.memsw.limit_in_bytes=2000000 memorylimit

sudo cgcreate -g blkio:iolimit
sudo cgset -r blkio.throttle.read_bps_device="8:0 1000000"
sudo cgset -r blkio.throttle.write_bps_device="8:0 1000000"

sudo ./cpulimit_test abc




