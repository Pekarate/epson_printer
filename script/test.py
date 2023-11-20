import esc_pos_decoder
import io, os
from PIL import Image, ImageDraw

def esc_pos_to_image(filename):
    # Read the file
    with open(filename, "rb") as f:
        data = f.read()
    
    # Image dimensions and background color
    width = 400
    height = 900
    background_color = (255, 255, 255)
    
    # Parse ESC/POS data
    decoder = esc_pos_decoder.EscPosDecoder(verbose=0)
    decoder.feed_bytes(data)
    text = decoder.get_text()

    # Create a new image
    image = Image.new("RGB", (width, height), background_color)
    draw = ImageDraw.Draw(image)

    # Add text to the image
    if text:
        draw.text((10, 250), text, fill=(0, 0, 0))

    # Add a logo
    receipt_logo_path = "logo.png"
    if os.path.isfile(receipt_logo_path):
        with Image.open(receipt_logo_path) as receipt_logo:
            image.paste(receipt_logo, (30, 10))
        os.remove(receipt_logo_path)

    # Save the image in memory and as a file
    in_mem_file = io.BytesIO()
    image.save(in_mem_file, format="PNG")
    in_mem_file.seek(0)
    

    # Save the image as a file
    output_filename = f"{filename}.png"
    image.save(output_filename)

    print(f"Image saved as {output_filename}.")

# Call the function
esc_pos_to_image("node_print_data-11.bin")