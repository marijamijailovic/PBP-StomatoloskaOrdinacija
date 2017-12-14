PROGS = dentalClinic
CC = gcc
CCFLAGS	= -g -Wall `mysql_config --cflags --libs`
OBJ 	= dentalClinic.o	\
				patient.o \
				intervention.o	\
				material.o \
				employees.o

%.o: %.c
	$(CC) -c -o $@ $< $(CCFLAGS)

$(PROGS): $(OBJ)
	$(CC) -o $@ $^ $(CCFLAGS)

.PHONY: clean create trigger insert

create:
	mysql -u root -p  -D mysql <create.sql

trigger:
	mysql -u root -p  -D mysql <trigger.sql

insert:
	mysql -u root -p  -D mysql <insert.sql

clean:
	rm -rf $(PROGS) rm -rf *.o rm -r *~
