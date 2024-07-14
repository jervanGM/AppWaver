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

def generate_index_md(headers, u_headers):
    with open("index.md", 'w') as file:
        file.write("## List of files\n\n")
        file.write("## Component list\n\n")
        for header in headers:
            header_name = os.path.splitext(os.path.basename(header))[0].replace('_', ' ').title()
            header_path = os.path.basename(header).replace('_', '__').replace('.', '_8')
            file.write(f"- [{header_name}]({header_path}.html)\n")
            
        file.write("\n## Utilities list\n\n")
        for header in u_headers:
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
    include_dir = os.path.abspath("../../include")
    include_udir = os.path.abspath("../../utilities")
    if not os.path.isdir(include_dir):
        print(f"Error: {include_dir} is not a valid directory.")
        sys.exit(1)

    headers = get_header_files(include_dir)
    u_headers = get_header_files(include_udir)
    generate_index_md(headers,u_headers)
    print("index.md has been generated successfully.")

    run_doxygen()



