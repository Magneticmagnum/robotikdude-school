all: symlink link mkdir getcwd file_exists is_dir rename size perm copy myls
mkdir: mkdir.c
	gcc -o mkdir mkdir.c
getcwd: getcwd.c
	gcc -o getcwd getcwd.c
file_exists:file_exists.c
	gcc -o file_exists file_exists.c
is_dir:is_dir.c
	gcc -o is_dir is_dir.c
rename:rename.c
	gcc -o rename rename.c
size:size.c
	gcc -o size size.c
perm: perm.c
	gcc -o perm perm.c
copy:copy.c
	gcc -o copy copy.c
myls:myls.c
	gcc -o myls myls.c
link: link.c
	gcc -o link link.c
symlink: symlink.c
	gcc -o symlink symlink.c
clean:
	rm mkdir getcwd file_exists is_dir rename size perm copy myls link symlink

