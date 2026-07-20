#include <stdio.h>
#include "pico/stdlib.h"

#include "pb_encode.h"
#include "pb_decode.h"
#include "protos/message.pb.h"

#define BUF_LEN 64

int main() {
	stdio_init_all();

	Message msg = Message_init_zero;

	uint8_t buf[BUF_LEN];
	uint8_t bytes_written = 0;

	msg.val1 = 1;
	msg.val2 = 5.5;
	msg.val3 = 54;

	while (1) {

		pb_ostream_t stream = pb_ostream_from_buffer(buf, sizeof(buf));

		uint8_t status = pb_encode(&stream, Message_fields, &msg);
		bytes_written = stream.bytes_written;

		printf("%d bytes written: ", bytes_written);
		for (int i=0; i<bytes_written; i++) {
			printf("%02x", buf[i]);
			if (i%2) {
				printf(" ");
			}
		}
		printf("\n");

		sleep_ms(1000);
	}
	return 0;
}
