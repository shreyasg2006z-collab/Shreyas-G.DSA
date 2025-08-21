#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a page in history
typedef struct Page {
    char url[256];
    struct Page* next;
    struct Page* prev;
} Page;

// Structure for a tab (node)
typedef struct Tab {
    int tab_id;
    Page* current_page;
    Page* history_head;
    struct Tab* next;
} Tab;

// Global variables
Tab* head_tab = NULL;
Tab* current_tab = NULL;
int tab_counter = 1;

// Function declarations
void visitNewPage();
void goForward();
void goBack();
void showCurrentTab();
void closeCurrentTab();
void showHistory();
Tab* createNewTab();
Page* createNewPage(char* url);
void addPageToHistory(Tab* tab, char* url);

// Create a new tab
Tab* createNewTab() {
    Tab* new_tab = (Tab*)malloc(sizeof(Tab));
    new_tab->tab_id = tab_counter++;
    new_tab->current_page = NULL;
    new_tab->history_head = NULL;
    new_tab->next = NULL;

    if (head_tab == NULL) {
        head_tab = new_tab;
        current_tab = new_tab;
    } else {
        Tab* temp = head_tab;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_tab;
        current_tab = new_tab;
    }

    printf("New tab created with ID: %d\n", new_tab->tab_id);
    return new_tab;
}

// Create a new page
Page* createNewPage(char* url) {
    Page* new_page = (Page*)malloc(sizeof(Page));
    strcpy(new_page->url, url);
    new_page->next = NULL;
    new_page->prev = NULL;
    return new_page;
}

// Add page to history
void addPageToHistory(Tab* tab, char* url) {
    Page* new_page = createNewPage(url);

    if (tab->history_head == NULL) {
        tab->history_head = new_page;
        tab->current_page = new_page;
    } else {
        // Remove all forward history when visiting a new page
        Page* temp = tab->current_page;
        while (temp->next != NULL) {
            Page* to_delete = temp->next;
            temp->next = to_delete->next;
            if (to_delete->next != NULL) {
                to_delete->next->prev = temp;
            }
            free(to_delete);
        }

        // Add new page
        tab->current_page->next = new_page;
        new_page->prev = tab->current_page;
        tab->current_page = new_page;
    }
}

void visitNewPage() {
    char url[256];

    if (current_tab == NULL) {
        current_tab = createNewTab();
    }

    printf("Enter the URL to visit: ");
    scanf("%s", url);

    addPageToHistory(current_tab, url);
    printf("Visited: %s\n", url);
}

void goBack() {
    if (current_tab == NULL) {
        printf("No tab is currently open.\n");
        return;
    }

    if (current_tab->current_page == NULL || current_tab->current_page->prev == NULL) {
        printf("No previous page in history.\n");
        return;
    }

    current_tab->current_page = current_tab->current_page->prev;
    printf("Went back to: %s\n", current_tab->current_page->url);
}

void goForward() {
    if (current_tab == NULL) {
        printf("No tab is currently open.\n");
        return;
    }

    if (current_tab->current_page == NULL || current_tab->current_page->next == NULL) {
        printf("No forward page in history.\n");
        return;
    }

    current_tab->current_page = current_tab->current_page->next;
    printf("Went forward to: %s\n", current_tab->current_page->url);
}

void showCurrentTab() {
    if (current_tab == NULL) {
        printf("No tab is currently open.\n");
        return;
    }

    printf("Current Tab ID: %d\n", current_tab->tab_id);
    if (current_tab->current_page != NULL) {
        printf("Current Page: %s\n", current_tab->current_page->url);
    } else {
        printf("No page is currently loaded.\n");
    }
}

void closeCurrentTab() {
    if (current_tab == NULL) {
        printf("No tab is currently open.\n");
        return;
    }

    printf("Closing tab %d\n", current_tab->tab_id);

    // Free all pages in history
    Page* page = current_tab->history_head;
    while (page != NULL) {
        Page* temp = page;
        page = page->next;
        free(temp);
    }

    // Remove tab from linked list
    if (current_tab == head_tab) {
        head_tab = head_tab->next;
        free(current_tab);
        current_tab = head_tab;
    } else {
        Tab* temp = head_tab;
        while (temp->next != current_tab) {
            temp = temp->next;
        }
        temp->next = current_tab->next;
        free(current_tab);
        current_tab = temp;
    }

    if (current_tab != NULL) {
        printf("Switched to tab %d\n", current_tab->tab_id);
    } else {
        printf("All tabs closed.\n");
    }
}

void showHistory() {
    if (current_tab == NULL) {
        printf("No tab is currently open.\n");
        return;
    }

    if (current_tab->history_head == NULL) {
        printf("No history available.\n");
        return;
    }

    printf("History for Tab %d:\n", current_tab->tab_id);
    Page* page = current_tab->history_head;
    int index = 1;

    while (page != NULL) {
        if (page == current_tab->current_page) {
            printf("%d. %s (current)\n", index, page->url);
        } else {
            printf("%d. %s\n", index, page->url);
        }
        page = page->next;
        index++;
    }
}

int main() {
    int choice;

    printf("Welcome to Browser Tab Manager!\n");

    while (1) {
        printf("\nSample Menu for user interaction:\n");
        printf("1. Visit a new page\n");
        printf("2. Go back\n");
        printf("3. Go forward\n");
        printf("4. Show current tab\n");
        printf("5. Close current tab\n");
        printf("6. Show history\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                visitNewPage();
                break;
            case 2:
                goBack();
                break;
            case 3:
                goForward();
                break;
            case 4:
                showCurrentTab();
                break;
            case 5:
                closeCurrentTab();
                break;
            case 6:
                showHistory();
                break;
            case 7:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
