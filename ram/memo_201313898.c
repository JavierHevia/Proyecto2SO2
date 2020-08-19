#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>
#include <linux/hugetlb.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>

#define BUFSIZE 150

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Escribir informacion de la memoria ram.");
MODULE_AUTHOR("Eduardo Javier Hevia Calderòn");

struct sysinfo inf;

static int escribir_archivo(struct seq_file *archivo, void *v)
{
    si_meminfo(&inf);
    long memoria_total = (inf.totalram * 4);
    long memoria_libre = (inf.freeram * 4);
    seq_printf(archivo, "{\n");
    seq_printf(archivo, "\"Meminfo\":{\n");

    seq_printf(archivo, " \"MemoriaTotal\":%8lu,\n", memoria_total / 1024);
    seq_printf(archivo, " \"MemoriaLibre\":%8lu,\n", memoria_libre / 1024);
    seq_printf(archivo, " \"MemoriaUsada\":%i\n", (memoria_libre * 100) / memoria_total);
    seq_printf(archivo, " }\n");
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
    proc_create("memo_201313898", 0, NULL, &operaciones);
    printk(KERN_INFO "Eduardo Javier Hevia Calderòn\n");
    return 0;
}

static void salir(void)
{
    remove_proc_entry("memo_201313898", NULL);
    printk(KERN_INFO "Sistemas Operativos 2\n");
}

module_init(iniciar);
module_exit(salir);
