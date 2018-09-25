extern char *pid;
extern char *uid;
extern int s;
extern int U;
extern int S;
extern int v;
extern int c;

int main (int argc, char *argv[]);
int readDirectory();
int readStat(char *pid1);
int readStatm(char *pid1);
int readStatus(char *pid1);
int readCmdline(char *pid1);
