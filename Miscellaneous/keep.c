while ((dup2(filedes[1], STDOUT_FILENO) == -1) && (errno == EINTR)) {}
close(filedes[1]);
/*
   A loop is needed to allow for the possibility of dup2 being interrupted by
   a signal.
*/
