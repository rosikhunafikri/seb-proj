import random

def generate_origin_and_axes():
    try:
        with open("dataset1_origin_and_axes.txt", "w") as file:
            for _ in range(25):
                file.write("{0.0, 0.0}\n")
                file.write(f"{{{random.choice([-1.0, 1.0])}, 0.0}}\n")
                file.write(f"{{0.0, {random.choice([-1.0, 1.0])}}}\n")
                file.write(f"{{{random.choice([-2.0, 2.0])}, 0.0}}\n")
        return True
    except Exception as e:
        print(f"Error generating dataset1_origin_and_axes.txt: {e}")
        return False

def generate_very_close_points():
    try:
        with open("dataset2_very_close_points.txt", "w") as file:
            for _ in range(100):
                base_x = 1.0 + random.uniform(0, 0.001)
                base_y = 1.0 + random.uniform(0, 0.001)
                file.write(f"{{{base_x:.8f}, {base_y:.8f}}}\n")
        return True
    except Exception as e:
        print(f"Error generating dataset2_very_close_points.txt: {e}")
        return False

def generate_large_and_small_values():
    try:
        with open("dataset3_large_and_small_values.txt", "w") as file:
            for _ in range(50):
                large_x = random.uniform(0, 1e9)
                large_y = random.uniform(0, 1e9)
                small_x = random.uniform(0, 1e-9)
                small_y = random.uniform(0, 1e-9)
                file.write(f"{{{large_x:.8f}, {large_y:.8f}}}\n")
                file.write(f"{{{small_x:.8f}, {small_y:.8f}}}\n")
        return True
    except Exception as e:
        print(f"Error generating dataset3_large_and_small_values.txt: {e}")
        return False

def generate_collinear_points():
    try:
        with open("dataset4_collinear_points.txt", "w") as file:
            for i in range(100):
                x = i / 2.0
                y = 2 * x
                file.write(f"{{{x:.8f}, {y:.8f}}}\n")
        return True
    except Exception as e:
        print(f"Error generating dataset4_collinear_points.txt: {e}")
        return False

def generate_identical_points():
    try:
        with open("dataset5_identical_points.txt", "w") as file:
            for _ in range(90):
                file.write("{2.0, 2.0}\n")
            for _ in range(10):
                x = 2.0 + random.uniform(0, 0.01)
                y = 2.0 + random.uniform(0, 0.01)
                file.write(f"{{{x:.8f}, {y:.8f}}}\n")
        return True
    except Exception as e:
        print(f"Error generating dataset5_identical_points.txt: {e}")
        return False

def generate_small_radius_cluster():
    try:
        with open("dataset6_small_radius_cluster.txt", "w") as file:
            for _ in range(100):
                x = random.uniform(0, 0.01)
                y = random.uniform(0, 0.01)
                file.write(f"{{{x:.8f}, {y:.8f}}}\n")
        return True
    except Exception as e:
        print(f"Error generating dataset6_small_radius_cluster.txt: {e}")
        return False

def generate_perpendicular_lines():
    try:
        with open("dataset7_perpendicular_lines.txt", "w") as file:
            for _ in range(50):
                x = random.uniform(0, 10.0)
                y = 0.0
                file.write(f"{{{x:.8f}, {y:.8f}}}\n")
            for _ in range(50):
                y = random.uniform(0, 10.0)
                x = 0.0
                file.write(f"{{{x:.8f}, {y:.8f}}}\n")
        return True
    except Exception as e:
        print(f"Error generating dataset7_perpendicular_lines.txt: {e}")
        return False

def main():
    success = True
    success &= generate_origin_and_axes()
    success &= generate_very_close_points()
    success &= generate_large_and_small_values()
    success &= generate_collinear_points()
    success &= generate_identical_points()
    success &= generate_small_radius_cluster()
    success &= generate_perpendicular_lines()

    if success:
        print("Datasets generated successfully.")
    else:
        print("One or more datasets failed to generate.")

if __name__ == "__main__":
    main()
