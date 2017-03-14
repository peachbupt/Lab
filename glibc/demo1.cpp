#include <glib.h>
#include <pthread.h>



gboolean timeout(gpointer data)
{
	int *n = (int*)data;
	g_debug("[%ld] -timeout- receive %d\n", pthread_self(), *n);
	*n += 1;
	return *n < 20;
}

gboolean idle(gpointer data)
{
	int *n = (int*)data;
	g_debug("[%ld] -idle- receive %d \n", pthread_self(), *n);
	*n += 1;
	return *n < 10;
}

gboolean source_timeout(gpointer data)
{
	static int index = 0;
	index++;
	g_debug("[%ld] - source_tiemout - monitor - %d\n", pthread_self(), index);
	if(index == 5)
	{
		g_main_loop_quit((GMainLoop*)data);
		return FALSE;
	}
	return TRUE;
}

void create_monitor_source(GMainContext *context, GMainLoop *loop)
{
	GSource *source = g_timeout_source_new(2000);
	int id = g_source_attach(source, context);
	g_source_set_callback(source, source_timeout, loop, NULL);
}

int main(int argc, char* argv[])
{
	int n = 0;
	GMainContext *context = g_main_context_default();
	g_debug("[%ld] hello world\n", pthread_self());
	GMainLoop *loop = g_main_loop_new(context, 0);
	create_monitor_source(context, loop);
	g_timeout_add(1000, timeout, &n);
	g_idle_add(idle, &n);
	g_main_loop_run(loop);
	return 0;
}
