#ifndef INTERVIEW_PUBSERV
#define INTERVIEW_PUBSERV

#include <checklst.hpp>

bool interview_start(TCheckListBox *lstbox);

void interview_create(void);

void interview_end(void);

int interview_get_count(void);

String interview_get_codes(TCheckListBox *lstbox);

void interview_set_codes(TCheckListBox *lstbox, String notes);

#endif
