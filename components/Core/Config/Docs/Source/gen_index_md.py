import os
import subprocess
import sys
import webbrowser

def get_header_files(include_dir):
    headers = []
    for root, dirs, files in os.walk(include_dir):
        for file in files:
            if file.endswith(".h"):
                headers.append(os.path.relpath(os.path.join(root, file), include_dir))
    return headers

def generate_index_md(hw_headers, sw_headers):
    with open("index.md", 'w') as file:
        file.write("# Component List\n\n")
        file.write("## Hardware Configuration Component list\n\n")
        for header in hw_headers:
            header_name = os.path.splitext(os.path.basename(header))[0].replace('_', ' ').title()
            header_path = os.path.basename(header).replace('_', '__').replace('.', '_8')
            file.write(f"- [{header_name}]({header_path}.html)\n")
            
        file.write("\n## Software Configuration Component list\n\n")
        for header in sw_headers:
            header_name = os.path.splitext(os.path.basename(header))[0].replace('_', ' ').title()
            header_path = os.path.basename(header).replace('_', '__').replace('.', '_8')
            file.write(f"- [{header_name}]({header_path}.html)\n")

def run_doxygen():
    result = subprocess.run(["doxygen", "Doxyfile"], capture_output=True)
    if result.returncode == 0:
        print("Doxygen documentation generated successfully.")
        # Abrir index.html en el navegador
        html_dir = os.path.join(os.getcwd(), "html")
        index_html = os.path.join(html_dir, "index.html")
        if os.path.exists(index_html):
            webbrowser.open(index_html)
        else:
            print(f"Error: {index_html} does not exist.")
    else:
        print("Error generating Doxygen documentation:")
        print(result.stderr.decode('utf-8'))

if __name__ == "__main__":
    include_hw_dir = os.path.abspath("../../Modules/HW_CFG/include")
    include_sw_dir = os.path.abspath("../../Modules/SW_CFG/include")
    if not os.path.isdir(include_hw_dir):
        print(f"Error: {include_hw_dir} is not a valid directory.")
        sys.exit(1)
        
    if not os.path.isdir(include_sw_dir):
        print(f"Error: {include_sw_dir} is not a valid directory.")
        sys.exit(1)

    hw_headers = get_header_files(include_hw_dir)
    sw_headers = get_header_files(include_sw_dir)
    generate_index_md(hw_headers,sw_headers)
    print("index.md has been generated successfully.")

    run_doxygen()



