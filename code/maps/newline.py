def add_newline_after_third_comma(input_file, output_file):
    with open(input_file, 'r') as file:
        content = file.read()

    modified_content = ""
    comma_count = 0

    for char in content:
        modified_content += char

        if char == ',':
            comma_count += 1

            if comma_count % 128 == 0:
                modified_content += '\n'

    with open(output_file, 'w') as file:
        file.write(modified_content)

    print(f"Modified content saved to '{output_file}'.")


# Usage example
input_file_path = 'input.txt'
output_file_path = 'output.txt'

add_newline_after_third_comma(input_file_path, output_file_path)
