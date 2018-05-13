
u_netlink: u_netlink.o
	$(CC) $(LDFLAGS) u_netlink.o -o u_netlink
u_netlink.o: u_netlink.c
	$(CC) $(CFLAGS) -c u_netlink.c
# remove object files and executable when user executes "make clean"
clean:
	rm *.o u_netlink
