#ifndef DISPATCH_CODE_H
#define DISPATCH_CODE_H

#include <err.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void embed_hidden_message(char *cover_text, int stride, const char *hidden);
void extract_hidden_message(const char *cover_text, int stride,
                            char *hidden_out, size_t size);

#endif // !DISPATCH_CODE_H
