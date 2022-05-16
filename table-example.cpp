#include <gtk/gtk.h>
#include <string> 

GtkWidget *window;
GtkWidget *table_box;

int random_between(int x, int y) {
    return x + (rand() % static_cast<int>(y - x + 1));
}

void delete_table() {
    GList *children, *iter;
    children = gtk_container_get_children(GTK_CONTAINER(table_box));
    for(iter=children; iter!=NULL; iter=g_list_next(iter))
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    g_list_free(children);
}

void fill_table(GtkWidget *table, int rows, int columns) {
    g_print("--------------------\n");
    for (int i=0; i<rows; i++) {
        for (int k=0; k<columns; k++) {
            int rnd = random_between(100, 999);
            std::string text = "[" + std::to_string(i) + "," + std::to_string(k) + "]:";
            text += std::to_string(rnd);
            GtkWidget *label0 = gtk_label_new(text.c_str());
            gtk_table_attach(GTK_TABLE(table), label0, i, i+1, k, k+1, GTK_FILL, GTK_FILL, 0, 0);
            g_print(text.c_str());
            g_print("  ");
        }
        g_print("\n");
    }
}

void create_table(GtkWidget *widget, gpointer data) {
    delete_table();
    int rows = random_between(3, 8);
    int columns = random_between(3, 8);
    GtkWidget *table = gtk_table_new(rows, columns, FALSE);
    gtk_table_set_col_spacings(GTK_TABLE(table), 5);
    fill_table(table, rows, columns);
    gtk_container_add(GTK_CONTAINER(table_box), table);
    gtk_widget_show_all(window);
}

int main(int argc, char *argv[]) {
    GtkWidget *vbox;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request (window, 300, 250);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_title(GTK_WINDOW(window), "::Test GTK3 Table::");
    gtk_container_set_border_width(GTK_CONTAINER(window), 15);

    vbox = gtk_vbox_new(TRUE, 5);
    table_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    
    GtkWidget *button1 = gtk_button_new_with_label("Update table");
    gtk_widget_set_size_request(button1, 70, 30);

    g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(create_table), NULL);

    gtk_container_add(GTK_CONTAINER(vbox), button1);
    gtk_container_add(GTK_CONTAINER(vbox), table_box);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), G_OBJECT(window));

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

