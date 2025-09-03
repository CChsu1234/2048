BUILD_DIR = build

.PHONY: load build run clean

load:
	cmake -S . -B $(BUILD_DIR)

build:
	cmake --build $(BUILD_DIR)

run:
	./$(BUILD_DIR)/2048

clean:
	rm -rf $(BUILD_DIR)
