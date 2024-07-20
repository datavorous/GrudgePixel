from PIL import Image
import os

def resize_pixel_art(input_path, output_path, target_size=None, scale_factor=None):
    with Image.open(input_path) as img:
        width, height = img.size
        
        if target_size:
            # Calculate scale factor based on the larger dimension
            scale_factor = max(target_size // width, target_size // height)
        
        new_width = width * scale_factor
        new_height = height * scale_factor
        
        resized_img = img.resize((new_width, new_height), Image.NEAREST)
        
        # Ensure output_path has a valid extension
        file_name, file_extension = os.path.splitext(output_path)
        if not file_extension:
            file_extension = os.path.splitext(input_path)[1]
            output_path = file_name + file_extension

        resized_img.save(output_path)
        
        print(f"Resized image saved to {output_path}")
        print(f"Original size: {width}x{height}")
        print(f"New size: {new_width}x{new_height}")

def get_valid_path(prompt, is_input=True):
    while True:
        path = input(prompt).strip()
        if is_input:
            if os.path.isfile(path):
                return path
            else:
                print("Error: File does not exist. Please enter a valid file path.")
        else:
            directory = os.path.dirname(path)
            if not directory:
                directory = os.getcwd()
            if not os.path.exists(directory):
                print("Error: Output directory does not exist. Please enter a valid directory path.")
            else:
                return path

def get_resize_option():
    while True:
        choice = input("Choose resize option:\n1. Scale factor\n2. Target size\nEnter 1 or 2: ").strip()
        if choice in ['1', '2']:
            return int(choice)
        print("Invalid choice. Please enter 1 or 2.")

def get_valid_scale_factor():
    while True:
        try:
            scale_factor = int(input("Enter the scale factor (e.g., 2 for 2x, 4 for 4x): "))
            if scale_factor > 0:
                return scale_factor
            else:
                print("Error: Scale factor must be a positive integer.")
        except ValueError:
            print("Error: Please enter a valid integer for the scale factor.")

def get_valid_target_size():
    while True:
        try:
            target_size = int(input("Enter the target size in pixels (e.g., 256 or 512): "))
            if target_size > 0:
                return target_size
            else:
                print("Error: Target size must be a positive integer.")
        except ValueError:
            print("Error: Please enter a valid integer for the target size.")

def main():
    print("Welcome to the Enhanced Pixel Art Resizer!")
    
    input_path = get_valid_path("Enter the path to the input image file: ")
    output_path = get_valid_path("Enter the path to save the resized image: ", is_input=False)
    
    resize_option = get_resize_option()
    
    if resize_option == 1:
        scale_factor = get_valid_scale_factor()
        resize_pixel_art(input_path, output_path, scale_factor=scale_factor)
    else:
        target_size = get_valid_target_size()
        resize_pixel_art(input_path, output_path, target_size=target_size)

if __name__ == "__main__":
    main()