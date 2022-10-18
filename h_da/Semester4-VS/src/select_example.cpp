const int SIZE = 10;
fd_set readfds;
int sockets[SIZE];

// fill sockets-array here

while (1)
{
    FD_ZERO(&readfds);             // remove all socket from set
    for (int i = 0; i < SIZE; ++i) // fill fd_set
        FD_SET(sockets[i], &readfds);

    // here we specify a fd_set to wait for reads, we could also wait for writes or errors, but leave this NULL, because we are not interested
    if (select(FD_SETSIZE, &readfds, NULL, NULL, NULL) < 0)
    {
        perror("Server: select error");
    }

    for (int i = 0; i < SIZE; ++i)
    {
        if (FD_ISSET(i, &readfds))
        {
            // read data from socket i
            // you can also start a new thread to do that, then this thread will be back on other requests earlier
        }
    }
}