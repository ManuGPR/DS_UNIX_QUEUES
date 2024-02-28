int init();
int set_value(int key, char *value1, int N_value2, double *V_value2);
int get_value(int key, char *value1, int *N_value2, double *V_value2);
int modify_value(int key, char *value1, int N_value2, double V_value2);
int delete_key(int key);
int exist(int key);

mqd_t q_server;
size_t cero = 0;
struct mq_attr attr;

