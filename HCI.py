import tkinter as tk
from tkinter import messagebox, ttk

class StudentInternshipApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Student and Management System")
        self.root.geometry("500x400")                                      

        # Student information frame
        self.frame = tk.Frame(self.root)
        self.frame.pack(pady=10)

        # Input fields
        self.name_label = tk.Label(self.frame, text="Name:")
        self.name_label.grid(row=0, column=0, padx=10, pady=10)
        self.name_entry = tk.Entry(self.frame)
        self.name_entry.grid(row=0, column=1)

        self.age_label = tk.Label(self.frame, text="Age:")
        self.age_label.grid(row=1, column=0, padx=10, pady=10)
        self.age_entry = tk.Entry(self.frame)
        self.age_entry.grid(row=1, column=1)

        self.department_label = tk.Label(self.frame, text="Department:")
        self.department_label.grid(row=2, column=0, padx=10, pady=10)
        self.department_entry = tk.Entry(self.frame)
        self.department_entry.grid(row=2, column=1)

        # Add Student button
        self.add_button = tk.Button(self.root, text="Add Student", command=self.add_student)
        self.add_button.pack(pady=10)

        # **Remove Student button**
        # Adds a button that will call the remove_student method to delete the selected student from the Treeview
        self.remove_button = tk.Button(self.root, text="Remove Student", command=self.remove_student)
        self.remove_button.pack(pady=10)

        # Treeview for displaying students
        self.tree = ttk.Treeview(self.root, columns=("Name", "Age", "Department"), show='headings')
        self.tree.heading("Name", text="Name")
        self.tree.heading("Age", text="Age")
        self.tree.heading("Department", text="Department")
        self.tree.pack(pady=20)

    # Method to add a student to the Treeview
    def add_student(self):
        name = self.name_entry.get()
        age = self.age_entry.get()
        department = self.department_entry.get()

        if name and age and department:
            self.tree.insert("", "end", values=(name, age, department))
            self.clear_entries()
        else:
            messagebox.showwarning("Input Error", "Please fill in all fields.")

    # **Method to remove a selected student from the Treeview**
    # Checks if an item is selected; if so, deletes it from the Treeview
    def remove_student(self):
        selected_item = self.tree.selection()
        if selected_item:
            self.tree.delete(selected_item)
        else:
            messagebox.showwarning("Selection Error", "Please select a student to remove.")

    # Clears the input fields after adding a student
    def clear_entries(self):
        self.name_entry.delete(0, tk.END)
        self.age_entry.delete(0, tk.END)
        self.department_entry.delete(0, tk.END)

if __name__ == "__main__":
    root = tk.Tk()
    app = StudentInternshipApp(root)
    root.mainloop()