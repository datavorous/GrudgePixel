import tkinter as tk
from tkinter import filedialog, messagebox
from PIL import Image, ImageEnhance, ImageFilter, ImageTk
import os

def load_image():
    global image, temp_image, image_stack
    file_path = filedialog.askopenfilename()
    if file_path:
        image = Image.open(file_path)
        temp_image = image.copy()
        image_stack = [temp_image.copy()]
        update_image_display(temp_image)
        messagebox.showinfo("Image Loaded", "Image loaded successfully.")

def save_image():
    if temp_image:
        output_path = filedialog.asksaveasfilename(defaultextension=".png", filetypes=[("PNG files", "*.png"), ("All files", "*.*")])
        if output_path:
            temp_image.save(output_path)
            messagebox.showinfo("Image Saved", f"Enhanced image saved to {output_path}")
    else:
        messagebox.showerror("Error", "No image loaded.")

def undo_image():
    global temp_image
    if len(image_stack) > 1:
        image_stack.pop()
        temp_image = image_stack[-1].copy()
        update_image_display(temp_image)
    else:
        messagebox.showinfo("Undo", "No more actions to undo.")

def resize_image():
    global temp_image
    if temp_image:
        scale_factor = float(resize_entry.get())
        temp_image = resize_pixel_perfect(temp_image, scale_factor)
        image_stack.append(temp_image.copy())
        update_image_display(temp_image)
    else:
        messagebox.showerror("Error", "No image loaded.")

def adjust_chroma_image():
    global temp_image
    if temp_image:
        factor = float(chroma_entry.get())
        temp_image = adjust_chroma(temp_image, factor)
        image_stack.append(temp_image.copy())
        update_image_display(temp_image)
    else:
        messagebox.showerror("Error", "No image loaded.")

def enhance_outline_image():
    global temp_image
    if temp_image:
        strength = float(outline_entry.get())
        temp_image = enhance_outline(temp_image, strength)
        image_stack.append(temp_image.copy())
        update_image_display(temp_image)
    else:
        messagebox.showerror("Error", "No image loaded.")

def optimize_palette_image():
    global temp_image
    if temp_image:
        num_colors = int(palette_entry.get())
        temp_image = optimize_palette(temp_image, num_colors)
        image_stack.append(temp_image.copy())
        update_image_display(temp_image)
    else:
        messagebox.showerror("Error", "No image loaded.")

def apply_dithering_image():
    global temp_image
    if temp_image:
        dither_method = dither_var.get()
        temp_image = apply_dithering(temp_image, dither_method)
        image_stack.append(temp_image.copy())
        update_image_display(temp_image)
    else:
        messagebox.showerror("Error", "No image loaded.")

def update_image_display(img):
    global tk_image
    tk_image = ImageTk.PhotoImage(img)
    canvas.create_image(0, 0, anchor=tk.NW, image=tk_image)
    canvas.config(scrollregion=canvas.bbox(tk.ALL))

def resize_pixel_perfect(image, scale_factor):
    width, height = image.size
    new_width = int(width * scale_factor)
    new_height = int(height * scale_factor)
    return image.resize((new_width, new_height), Image.NEAREST)

def adjust_chroma(image, factor):
    enhancer = ImageEnhance.Color(image)
    return enhancer.enhance(factor)

def enhance_outline(image, strength):
    rgb_image = image.convert('RGB')
    grayscale = rgb_image.convert('L')
    edges = grayscale.filter(ImageFilter.FIND_EDGES)
    edges = ImageEnhance.Brightness(edges).enhance(strength)
    mask = Image.eval(edges, lambda x: 255 if x > 128 else 0)
    outlined = Image.composite(rgb_image, Image.new('RGB', rgb_image.size, 'black'), mask)
    return Image.blend(rgb_image, outlined, 0.5)

def optimize_palette(image, num_colors):
    return image.quantize(colors=num_colors, method=2)

def apply_dithering(image, method='floyd-steinberg'):
    if method == 'floyd-steinberg':
        return image.convert('P', palette=Image.ADAPTIVE, colors=256).convert('RGB')
    else:
        raise ValueError("Unsupported dithering method")

app = tk.Tk()
app.title("Pixel Art Enhancer")

# GitHub dark palette colors
bg_color = '#0d1117'
fg_color = '#c9d1d9'
btn_color = '#21262d'
entry_color = '#30363d'
highlight_color = '#58a6ff'

# Set the overall background color
app.configure(bg=bg_color)

# Update the canvas background
canvas = tk.Canvas(app, borderwidth=0, bg=bg_color)
canvas.grid(row=0, column=0, columnspan=3)

v_scrollbar = tk.Scrollbar(app, orient=tk.VERTICAL, command=canvas.yview, bg=btn_color, troughcolor=entry_color)
v_scrollbar.grid(row=0, column=3, sticky='ns')
canvas.config(yscrollcommand=v_scrollbar.set)

h_scrollbar = tk.Scrollbar(app, orient=tk.HORIZONTAL, command=canvas.xview, bg=btn_color, troughcolor=entry_color)
h_scrollbar.grid(row=1, column=0, columnspan=3, sticky='ew')
canvas.config(xscrollcommand=h_scrollbar.set)

# Load and Save buttons
tk.Button(app, text="Load Image", command=load_image, bg=btn_color, fg=fg_color, highlightbackground=highlight_color).grid(row=2, column=0, pady=5)
tk.Button(app, text="Save Image", command=save_image, bg=btn_color, fg=fg_color, highlightbackground=highlight_color).grid(row=2, column=1, pady=5)
tk.Button(app, text="Undo", command=undo_image, bg=btn_color, fg=fg_color, highlightbackground=highlight_color).grid(row=2, column=2, pady=5)

# Resize
tk.Label(app, text="Resize Factor:", bg=bg_color, fg=fg_color).grid(row=3, column=0, pady=5)
resize_entry = tk.Entry(app, bg=entry_color, fg=fg_color, highlightbackground=highlight_color)
resize_entry.grid(row=3, column=1, pady=5)
tk.Button(app, text="Resize", command=resize_image, bg=btn_color, fg=fg_color, highlightbackground=highlight_color).grid(row=3, column=2, pady=5)

# Chroma Boost
tk.Label(app, text="Chroma Boost Factor:", bg=bg_color, fg=fg_color).grid(row=4, column=0, pady=5)
chroma_entry = tk.Entry(app, bg=entry_color, fg=fg_color, highlightbackground=highlight_color)
chroma_entry.grid(row=4, column=1, pady=5)
tk.Button(app, text="Boost Chroma", command=adjust_chroma_image, bg=btn_color, fg=fg_color, highlightbackground=highlight_color).grid(row=4, column=2, pady=5)

# Outline Enhancement
tk.Label(app, text="Outline Enhancement Strength:", bg=bg_color, fg=fg_color).grid(row=5, column=0, pady=5)
outline_entry = tk.Entry(app, bg=entry_color, fg=fg_color, highlightbackground=highlight_color)
outline_entry.grid(row=5, column=1, pady=5)
tk.Button(app, text="Enhance Outline", command=enhance_outline_image, bg=btn_color, fg=fg_color, highlightbackground=highlight_color).grid(row=5, column=2, pady=5)

# Palette Optimization
tk.Label(app, text="Number of Colors:", bg=bg_color, fg=fg_color).grid(row=6, column=0, pady=5)
palette_entry = tk.Entry(app, bg=entry_color, fg=fg_color, highlightbackground=highlight_color)
palette_entry.grid(row=6, column=1, pady=5)
tk.Button(app, text="Optimize Palette", command=optimize_palette_image, bg=btn_color, fg=fg_color, highlightbackground=highlight_color).grid(row=6, column=2, pady=5)

# Dithering
tk.Label(app, text="Dithering Method:", bg=bg_color, fg=fg_color).grid(row=7, column=0, pady=5)
dither_var = tk.StringVar(value='floyd-steinberg')
tk.OptionMenu(app, dither_var, 'floyd-steinberg').grid(row=7, column=1, pady=5)
tk.Button(app, text="Apply Dithering", command=apply_dithering_image, bg=btn_color, fg=fg_color, highlightbackground=highlight_color).grid(row=7, column=2, pady=5)

app.mainloop()
