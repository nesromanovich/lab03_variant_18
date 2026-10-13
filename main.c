#include <stdio.h>
#include <limits.h>

int main(void) {
    int N, V, A;

    printf("Введите N (макс. сторона, 1..50): ");
    if (scanf("%d", &N) != 1) {
        printf("Ошибка: N должно быть целым числом.\n");
        return 1;
    }

    printf("Введите V (требуемый объем, >0): ");
    if (scanf("%d", &V) != 1) {
        printf("Ошибка: V должно быть целым числом.\n");
        return 1;
    }

    printf("Введите A (предельная площадь, >0): ");
    if (scanf("%d", &A) != 1) {
        printf("Ошибка: A должно быть целым числом.\n");
        return 1;
    }

    if (N < 1 || N > 50) {
        printf("Ошибка: N вне диапазона 1..50.\n");
        return 1;
    }
    if (V <= 0) {
        printf("Ошибка: V должно быть > 0.\n");
        return 1;
    }
    if (A <= 0) {
        printf("Ошибка: A должно быть > 0.\n");
        return 1;
    }

    int count = 0;
    int found = 0;
    int bestExtra = INT_MAX;
    int bestSurface = INT_MAX;
    int bestL = 0, bestW = 0, bestH = 0;
    long long innerIters = 0;

    for (int l = 1; l <= N; l++) {
        for (int w = l; w <= N; w++) {
            for (int h = w; h <= N; h++) {
                innerIters++;

                int volume = l * w * h;
                if (volume < V) continue;

                int surface = 2 * (l * w + l * h + w * h);
                if (surface > A) continue;

                int extra = volume - V;

                count++;
                found = 1;

                printf("(%d, %d, %d): V=%d, S=%d, extra=%d\n",
                       l, w, h, volume, surface, extra);

                if (extra < bestExtra ||
                    (extra == bestExtra && surface < bestSurface)) {
                    bestExtra = extra;
                    bestSurface = surface;
                    bestL = l;
                    bestW = w;
                    bestH = h;
                }
            }
        }
    }

    printf("\n--- Итоги ---\n");
    if (!found) {
        printf("Подходящих коробок нет.\n");
    } else {
        printf("Подходящих коробок: %d\n", count);
        printf("Лучшая: (%d, %d, %d), лишний объем=%d, площадь=%d\n",
               bestL, bestW, bestH, bestExtra, bestSurface);
    }
    printf("Выполнений тела внутреннего цикла: %lld\n", innerIters);

    return 0;
}