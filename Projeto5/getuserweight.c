#include <linux/unistd.h>
#include <linux/sched/user.h>
#include <linux/cred.h>
#include <linux/linkage.h>

asmlinkage uid_t sys_getuserweight(int id){

	struct user_struct *usuario;

	kuid_t kid;

	if (id<-1)
		return -EINVAL;

	if (id==-1)
		kid.val = current_uid().val;
	else
		kid.val = id;
	

	usuario = find_user(kid);

	if (usuario !=  NULL)
		return usuario->pesoUsuario;
	
	return -EINVAL;
}
