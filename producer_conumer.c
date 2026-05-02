#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE], in = 0, out = 0;
sem_t empty, full;
pthread_mutex_t mutex;

void* producer(void* arg) {
    for(int i = 0; i < 5; i++) {
        int item = rand() % 100;
        sem_wait(&empty); pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Producer produced: %d at %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex); sem_post(&full);
        sleep(1);
    }
}

void* consumer(void* arg) {
    for(int i = 0; i < 5; i++) {
        sem_wait(&full); pthread_mutex_lock(&mutex);
        int item = buffer[out];
        printf("Consumer consumed: %d from %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex); sem_post(&empty);
        sleep(2);
    }
}

int main() {
    pthread_t p, c;
    sem_init(&empty, 0, BUFFER_SIZE); sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);
    pthread_join(p, NULL); pthread_join(c, NULL);
    return 0;
}