#ifndef FUNC_H
#define FUNC_H

//Tag
struct complex_tag{
        double real;
        double imaginary;
};

//Type
typedef struct{
        double real;
        double imaginary;
} Complex_type;

Complex_type multiply(struct complex_tag x, struct complex_tag y);

int division(struct complex_tag *a, struct complex_tag *b, struct complex_Tag *result);

int sumDif(struct complex_tag a, struct complex_tag b, struct complex_tag **sum, struct complex_tag **dif);

#endif

