sudo cgcreate -g cpu:/container
sudo cgset -r cpu.cfs_period_us=1000000 container
sudo cgset -r cpu.cfs_quota_us=100000 container

sudo cgcreate -g memory:/container
sudo cgset -r memory.limit_in_bytes=30000000 container

sudo cgcreate -g blkio:/container
sudo cgset -r blkio.throttle.read_bps_device="259:0 1000000" container
sudo cgset -r blkio.throttle.write_bps_device="259:0 1000000" container

sudo unzip capsule.zip
sudo ./cpulimit_test abc




