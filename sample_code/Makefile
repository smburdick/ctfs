default: babyfmt_level1 babyrev_level3 babyshell_level12 babystack_level3

babyfmt_level1: babyfmt_level1.c
	gcc -no-pie -fno-stack-protector -fno-omit-frame-pointer -z execstack -Wl,-z,relro,-z,lazy -w -x c babyfmt_level1.c -o babyfmt_level1

babyrev_level3: babyrev_level3.c
	gcc -W -z relro -z lazy -w -x c babyrev_level3.c -o babyrev_level3

babyshell_level12: babyshell_level12.c
	gcc -fstack-protector -Wl,-z,relro,-z,lazy -w -x c babyshell_level12.c -o babyshell_level12 -lcapstone

babystack_level3: babystack_level3.c
	gcc -no-pie -fno-stack-protector -fno-omit-frame-pointer -Wl,--no-as-needed -z execstack -Wl,-z,norelro -w babystack_level3.c -o babystack_level3
