# Trabalho 5 de MC504

## Preparação do ambiente

(Adaptado de: https://www.ic.unicamp.br/~islene/1s2017-mc504/proj2/qemu.html)

1. Obtenha a versão `4.11.3` do kernel e descompacte o arquivo:
```
wget https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-4.11.3.tar.xz
tar xJvf linux-4.11.3.tar.xz
```
2. No mesmo diretório, adicione:
* a imagem [ArchLinux_mc504.cow](https://www.ic.unicamp.br/~islene/1s2017-mc504/proj2/ArchLinux_mc504.cow), 
* o arquivo de configuração [config-4.11.3](https://www.ic.unicamp.br/~islene/1s2017-mc504/proj2/config-4.11.3),
* e [minhaChamadaSys.c](minhaChamadaSys.c).
3. Instale o arquivo de configuração:
```
cd linux-4.11.3
cp ../config-4.11.3 .config
```
4. Adicione o arquivo [user.c](user.c) em `linux-4.11.3/kernel`;
5. Adicione o arquivo [user.h](user.h) em `linux-4.11.3/include/linux/sched`;
6. Adicione os arquivos [getuserweight.c](getuserweight.c), [setuserweight.c](setuserweight.c) e [Makefile](Makefile) em `linux-4.11.3/arch/x86/kernel`;
7. Altere o arquivo [syscall_32.tbl](syscall_32.tbl) em `linux-4.11.3/arch/x86/syscalls/syscall_32.tbl` adicionando as syscalls criadas:
![image](https://user-images.githubusercontent.com/6686318/126048425-fcba765d-c871-421d-abdf-7c812c65d45f.png)
8. Altere o arquivo [minhaChamadaSys.c](minhaChamadaSys.c) já adicionado corrigindo os códigos das syscalls criadas.

## Teste das syscalls
1. Compile o kernel:
```
make -j$(nproc)
```
2. Teste o kernel com a imagem utilizando o QEMU:
```
qemu-system-i386 -hda ArchLinux_mc504.cow -kernel linux-4.11.3/arch/i386/boot/bzImage -append "rw root=/dev/hda" -drive format=raw,file=minhaChamadaSys.c
```
3. Quando o sistema carregar, faça login com "root", sem senha;
4. Se necessário, dentro do QEMU altere o mapa do teclado com:
```
loadkeys /usr/share/kbd/keymaps/i386/qwerty/br-abnt2.map.gz
```
5. Para finalmente testar as syscalls criadas, execute:
```
cat /dev/hdb > minhaChamadaSys.c
gcc minhaChamadaSys.c -o m
./m
```
6. Realize os testes:

![image](https://user-images.githubusercontent.com/6686318/126049387-715ffc68-3137-4e96-8212-0c0a016a63ba.png)

7. Para sair sem corromper a imagem:
```
poweroff
``` 
