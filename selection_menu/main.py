import tkinter as tk
import subprocess

class App(tk.Tk):
    def __init__(self):
        super().__init__()
        self.search = int
        self.url = None
        self.words = None
        self.tags = None
        self.domain = None

        self.label1 = tk.Label(self, text="Введите URL странички для поиска по ней:",
                              font=("Arial", 18))
        self.label1.pack(pady=(30, 20))

        self.input_field1 = tk.Entry(self, width=30)
        self.input_field1.pack()

        self.save_button = tk.Button(self, text="Сохранить", command=self.searchSelection)
        self.save_button.pack(pady=10)

    # МЕТОДЫ
    def inputWords(self):
        self.label3 = tk.Label(self, text="Введите слова через пробел, которые хотите найти:",
                               font=("Arial", 16))
        self.label3.pack(pady=(30, 20))
        self.input_field = tk.Entry(self, width=30)
        self.input_field.pack()
        self.save_button = tk.Button(self, text="Сохранить", command=self.saveWord)
        self.save_button.pack(pady=10)
    def saveWord(self):
        self.words = self.input_field.get()
        self.input_field.pack_forget()
        self.label3.pack_forget()
        self.save_button.pack_forget()

    def inputTags(self):
        self.label3 = tk.Label(self, text="Введите теги через пробел, тексты которых хотите найти:",
                               font=("Arial", 16))
        self.label3.pack(pady=(30, 20))
        self.input_field = tk.Entry(self, width=30)
        self.input_field.pack()
        self.save_button = tk.Button(self, text="Сохранить", command=self.saveTags)
        self.save_button.pack(pady=10)
    def saveTags(self):
        self.tags = self.input_field.get()
        self.input_field.pack_forget()
        self.label3.pack_forget()
        self.save_button.pack_forget()

    def inputWordsAndTags(self):
        self.label3 = tk.Label(self, text="Введите слова через пробел, которые хотите найти:",
                               font=("Arial", 16))
        self.label3.pack(pady=(30, 20))
        self.input_field = tk.Entry(self, width=30)
        self.input_field.pack()
        self.save_button = tk.Button(self, text="Сохранить", command=self.saveWordTags)
        self.save_button.pack(pady=10)
    def saveWordTags(self):
        self.words = self.input_field.get()
        self.input_field.pack_forget()
        self.label3.pack_forget()
        self.save_button.pack_forget()
        self.label3 = tk.Label(self, text="Введите теги через пробел, тексты которых хотите найти:",
                               font=("Arial", 16))
        self.label3.pack(pady=(30, 20))
        self.input_field = tk.Entry(self, width=30)
        self.input_field.pack()
        self.save_button = tk.Button(self, text="Сохранить", command=self.saveTagsWords)
        self.save_button.pack(pady=10)
    def saveTagsWords(self):
        self.tags = self.input_field.get()
        self.input_field.pack_forget()
        self.label3.pack_forget()
        self.save_button.pack_forget()
        self.print_results()

    def inputDomain(self):
        self.label3 = tk.Label(self, text="Введите один домен, ссылки с которым хотите найти:",
                               font=("Arial", 16))
        self.label3.pack(pady=(30, 20))
        self.input_field = tk.Entry(self, width=30)
        self.input_field.pack()
        self.save_button = tk.Button(self, text="Сохранить", command=self.saveDomain)
        self.save_button.pack(pady=10)
    def saveDomain(self):
        self.domain = self.input_field.get()
        self.input_field.pack_forget()
        self.label3.pack_forget()
        self.save_button.pack_forget()

    def searchSelection(self):
        self.url = self.input_field1.get()
        self.save_button.pack_forget()
        self.input_field1.pack_forget()
        self.label1.pack_forget()

        self.label2 = tk.Label(self, text="Выберите тип поиска по страничке:",
                              font=("Arial", 18))
        self.btn1 = tk.Button(self, text="Поиск слов", command=self.byWords,
                              height=1, width=15, font=("Arial", 9))
        self.btn2 = tk.Button(self, text="Поиск по тегам", command=self.byTags,
                              height=1, width=15, font=("Arial", 9))
        self.btn3 = tk.Button(self, text="Поиск слов в тегах", command=self.byTagsWords,
                              height=1, width=15, font=("Arial", 9))
        self.btn4 = tk.Button(self, text="Поиск ссылок", command=self.byLinks,
                              height=1, width=15, font=("Arial", 9))

        self.label2.pack(pady=(30, 20))
        self.btn1.place(relx=.1, rely=.5)
        self.btn2.place(relx=.3, rely=.5)
        self.btn3.place(relx=.5, rely=.5)
        self.btn4.place(relx=.7, rely=.5)

    def buttonHide(self):
        self.label2.pack_forget()
        self.btn1.place_forget()
        self.btn2.place_forget()
        self.btn3.place_forget()
        self.btn4.place_forget()

    def byWords(self):
        self.buttonHide()
        self.inputWords()
        self.search = 1
        self.print_results()
    def byTags(self):
        self.buttonHide()
        self.inputTags()
        self.search = 2
        self.print_results()
    def byTagsWords(self):
        self.buttonHide()
        self.inputWordsAndTags()
        self.search = 3
    def byLinks(self):
        self.buttonHide()
        self.inputDomain()
        self.search = 4
        self.print_results()

    def print_results(self):
        self.label2 = tk.Label(self, text="Ведется поиск",
                               font=("Arial", 22))
        self.label2.pack(pady=(30, 20))
        self.after(3000, self.destroy)


if __name__ == "__main__":
    app = App()
    app.geometry('600x180')
    app.title("BRUUUH")
    app.mainloop()
    #args = [str(app.search), app.words, app.tags, app.domain]
    with open('C:/Users/New/Downloads/temp/cProject/cmake-build-debug/selections.txt', 'w') as file:
        result = (f"search_mode={str(app.search)}\n" + (f"search_words={app.words}\n" if app.words else "") +
                  (f"search_tags={app.tags}\n" if app.tags else "") + (f"search_domain={app.domain}\n" if app.domain else ""))
        file.write(result)
    subprocess.run(['C:/Users/New/Downloads/temp/cProject/main.c'])

