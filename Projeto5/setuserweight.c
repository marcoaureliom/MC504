#include <linux/unistd.h>
#include <linux/sched/user.h>
#include <linux/cred.h>
#include <linux/linkage.h>

asmlinkage uid_t sys_setuserweight(int id, int peso){
	
	struct user_struct *usuario;

	kuid_t kid;
	kid.val = id;

	if (peso<0)
		return -EINVAL;

	if (current_uid().val)
		return EACCES;
	
	usuario = find_user(kid);

	if (usuario!=NULL){
		usuario->pesoUsuario = peso;
		return 0;
	}
	
	return -EINVAL;
	
}
