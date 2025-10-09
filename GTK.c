#include <gtk/gtk.h>
#include "header.h"

struct Widgets {
    GtkTextView* text_view;
    GtkImage* image_widget;
};

static void on_button_clicked(GtkWidget* button, gpointer user_data) {
    struct Widgets* widgets = user_data;

    GtkTextBuffer* buffer = gtk_text_view_get_buffer(widgets->text_view);
    GtkTextIter start, end;
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    char* text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    g_print("Texte entrer : %s\n", text);
   
    int i = run_sdl_image(text);
    if (i == 1)
        g_free(text);
    else
        gtk_image_set_from_file(widgets->image_widget, "Image.bmp");
        g_free(text);
        
}

static void rotate_right(GtkWidget* button, gpointer user_data) {
    struct Widgets* widgets = user_data;
    if (!widgets || !widgets->image_widget) return;

    GError* error = NULL;
    GdkPixbuf* pixbuf = gdk_pixbuf_new_from_file("Image.bmp", &error);
    if (!pixbuf) {
        g_print("Erreur lors du chargement de l'image : %s\n", error->message);
        g_error_free(error);
        return;
    }

    GdkPixbuf* rotated = gdk_pixbuf_rotate_simple(pixbuf, GDK_PIXBUF_ROTATE_CLOCKWISE);
    g_object_unref(pixbuf);


    gdk_pixbuf_save(rotated, "Image.bmp", "bmp", &error, NULL);
    gtk_image_set_from_pixbuf(widgets->image_widget, rotated);
    g_object_unref(rotated);

    g_print("Rotation à droite effectuée.\n");
}


static void rotate_left(GtkWidget* button, gpointer user_data) {
    struct Widgets* widgets = user_data;
    if (!widgets || !widgets->image_widget) return;

    GError* error = NULL;
    GdkPixbuf* pixbuf = gdk_pixbuf_new_from_file("Image.bmp", &error);
    if (!pixbuf) {
        g_print("Erreur lors du chargement de l'image : %s\n", error->message);
        g_error_free(error);
        return;
    }

 
    GdkPixbuf* rotated = gdk_pixbuf_rotate_simple(pixbuf, GDK_PIXBUF_ROTATE_COUNTERCLOCKWISE);
    g_object_unref(pixbuf);

    gdk_pixbuf_save(rotated, "Image.bmp", "bmp", &error, NULL);
    gtk_image_set_from_pixbuf(widgets->image_widget, rotated);
    g_object_unref(rotated);

    g_print("Rotation à gauche effectuée.\n");
}

static void activate(GtkApplication* app, gpointer user_data) {
    GtkWidget* window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Solver OCR");
    gtk_window_set_default_size(GTK_WINDOW(window), 1280, 720);

    GtkWidget* main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_window_set_child(GTK_WINDOW(window), main_box);

    // GtkImage to show image
    GtkWidget* image_widget = gtk_image_new();
    gtk_widget_set_hexpand(image_widget, TRUE);
    gtk_widget_set_vexpand(image_widget, TRUE);
    gtk_box_append(GTK_BOX(main_box), image_widget);

    // Box for text view + green button
    GtkWidget* input_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_append(GTK_BOX(main_box), input_box);

    // TextView
    GtkWidget* text_view = gtk_text_view_new();
    gtk_widget_set_size_request(text_view, 400, 50); 
    gtk_widget_set_hexpand(text_view, TRUE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_NONE);

    // Should up font
    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    GtkTextTag* tag = gtk_text_tag_new("big_font");
    g_object_set(tag, "size-points", 20, NULL);
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_apply_tag(buffer, tag, &start, &end);

    gtk_box_append(GTK_BOX(input_box), text_view);

    // Execute button
    GtkWidget* green_button = gtk_button_new_with_label("Executer");
    gtk_widget_set_size_request(green_button, 150, 50);

 
    GtkCssProvider* provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
        "button.my-green {"
        "  background: #4CAF50;"
        "  color: white;"
        "  font-weight: bold;"
        "  border-radius: 5px;"
        "}",
        -1);

    GtkStyleContext* context = gtk_widget_get_style_context(green_button);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_class(context, "my-green");

    gtk_box_append(GTK_BOX(input_box), green_button);

    // Box for rtotation button
    GtkWidget* rotate_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_halign(rotate_box, GTK_ALIGN_CENTER);
    gtk_box_set_homogeneous(GTK_BOX(rotate_box), TRUE);
    gtk_widget_set_halign(rotate_box, GTK_ALIGN_FILL);
    gtk_box_append(GTK_BOX(main_box), rotate_box);

    GtkWidget* left_button = gtk_button_new_with_label("Rotate Left");

    GtkWidget* right_button = gtk_button_new_with_label("Rotate Right");
    
    gtk_box_append(GTK_BOX(rotate_box), left_button);
    gtk_box_append(GTK_BOX(rotate_box), right_button);

    // Structure Widgets for callbacks
    struct Widgets* widgets = g_new0(struct Widgets, 1);
    widgets->text_view = GTK_TEXT_VIEW(text_view);
    widgets->image_widget = GTK_IMAGE(image_widget);

    // Connected callbacks
    g_signal_connect(green_button, "clicked", G_CALLBACK(on_button_clicked), widgets);
    g_signal_connect(left_button, "clicked", G_CALLBACK(rotate_left), widgets);
    g_signal_connect(right_button, "clicked", G_CALLBACK(rotate_right), widgets);

    gtk_widget_set_visible(window, TRUE);
}

int main(int argc, char** argv) {
 
    GtkApplication* app = gtk_application_new("com.LouisLeBg", G_APPLICATION_DEFAULT_FLAGS);
    
    int status;
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}