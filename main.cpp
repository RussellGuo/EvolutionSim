#include <stdio.h>

typedef size_t combination_item_t;

// clean a combination
void init_combination(combination_item_t combination[], const size_t shape_len) {
    for (size_t i = 0; i < shape_len; i++) {
        combination[i] = 0;
    }
}

// combination: in/out, will be +1
// shape, shape_len: in
// return true if it rewinded.
bool get_next_combination(combination_item_t combination[], const combination_item_t shape[], const size_t shape_len) {
    for (size_t i = 0; i <shape_len; i++) {
        combination_item_t &pos = combination[i];
        pos++;
        if (pos < shape[i]) {
            return false;
        }
        pos = 0;
    }
    return true;
}

int main()
{
    const combination_item_t shape[] = { 3, 3, 3, 3};
    const size_t shape_len = (sizeof shape)/ (sizeof (shape[0]));
    combination_item_t combination[shape_len];
    init_combination(combination, shape_len);

    for (;;) {
        bool is_last;
        ssize_t i;
        for (i = shape_len - 1; i >= 0; i--) {
            printf("%lu", combination[i]+1);
        }
        printf("\n");
        is_last = get_next_combination(combination, shape, shape_len);
        if (is_last) {
            break;
        }
    }

    return 0;
}
