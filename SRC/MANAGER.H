#ifndef MANAGER_H
#define MANAGER_H

void ManagerInit(char *file);

void ManagerClose();

int ManagerSize();

byte *ManagerGet(int index);

#endif