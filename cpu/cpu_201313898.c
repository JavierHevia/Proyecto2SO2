#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>
#include <linux/hugetlb.h>
#include <linux/sched/signal.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>

struct list_head *p;
struct task_struct *proceso, ts, *tsk;

#define BUFSIZE 150

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Lista de procesos...");
MODULE_AUTHOR("Eduardo Javier Hevia Calderòn");

static int escribir_archivo(struct seq_file *archivo, void *v)
{
    int pros = 0;
    int pros2 = 0;
    seq_printf(archivo, "{\n");
    for_each_process(proceso)
    {
        pros++;
    }
    for_each_process(proceso)
    {
        pros2++;
        seq_printf(archivo, "\"proceso%i\":{\n", pros2);
        seq_printf(archivo, "\"PID\": %d, \n", proceso->pid);
        seq_printf(archivo, "\"Nombre\": \"%s\", \n", proceso->comm);
        seq_printf(archivo, "\"Estado\": %ld, \n", proceso->state);
        seq_printf(archivo, "  \"children\":{\n");
        int cont = 0;
        int pro = 0;
        int pro2 = 0;
        list_for_each(p, &(proceso->children))
        {
            pro++;
        }
        list_for_each(p, &(proceso->children))
        {
            cont++;
            //seq_printf(archivo, "    -------------------------------\n");
            seq_printf(archivo, "   \"procesoh%i\":{\n", cont);
            ts = *list_entry(p, struct task_struct, sibling);
            seq_printf(archivo, "     \"Proceso padre\":%d,\n", proceso->pid);
            seq_printf(archivo, "     \"PID\":%d, \n", ts.pid);
            seq_printf(archivo, "     \"Nombre\":\"%s\",\n", ts.comm);
            seq_printf(archivo, "     \"Estado\":%ld \n", ts.state);

            pro2++;
            if (pro == pro2)
            {
                seq_printf(archivo, "    }\n");
            }
            else
            {
                seq_printf(archivo, "    },\n");
            }
        }
        seq_printf(archivo, "  }\n"); //children

        if (pros == pros2)
        {
            seq_printf(archivo, " }\n"); //proceso padre
        }
        else
        {
            seq_printf(archivo, " },\n"); //proceso padre
        }

        pro = 0;
        pro2 = 0;

    }
    seq_printf(archivo, "}\n");

    return 0;
}

static int al_abrir(struct inode *inode, struct file *file)
{
    return single_open(file, escribir_archivo, NULL);
}

static struct file_operations operaciones =
    {
        .open = al_abrir,
        .read = seq_read};

static int iniciar(void)
{
    proc_create("cpu_practica1", 0, NULL, &operaciones);
    printk(KERN_INFO "Practica 1 sopes 2\n");
    return 0;
}

static void salir(void)
{
    remove_proc_entry("cpu_practica1", NULL);
    printk(KERN_INFO "Sistemas Operativos 2\n");
}

module_init(iniciar);
module_exit(salir);
