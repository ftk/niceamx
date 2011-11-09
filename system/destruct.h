#ifndef DESTRUCT_H
#define DESTRUCT_H

#ifdef __GNUC__ // supports __attribute__((destructor))
#define DESTRUCTOR __attribute__((destructor)) static
#define INVOKE_DESTRUCTOR() (static_cast<void>(0))
#else
#define DESTRUCTOR
#define INVOKE_DESTRUCTOR() (destruct_all())

void destruct_all();
#endif



#endif

