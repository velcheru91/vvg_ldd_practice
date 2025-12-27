import os

def main():
	print("Hello world, python")
	os.chmod('/proc/ldd1_drvr', 0o777)
	drv_handle = open('/proc/ldd1_drvr')
	drv_handle.writelines("Hello kernel")
	msg_frm_kernel = drv_handle.readline()
	print(msg_frm_kernel)
	drv_handle.close()
	return

main()

