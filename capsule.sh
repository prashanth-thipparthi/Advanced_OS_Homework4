sudo cgcreate -g cpu:/cpulimit_test

sudo cgset -r cpu.cfs_period_us=1000000 cpulimit_test

sudo cgset -r cpu.cfs_quota_us=100000 cpulimit_test


