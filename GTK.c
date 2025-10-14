#include <gtk/gtk.h>
#include "header.h"
#include <math.h>
#include <cairo.h>



struct Widgets {
    GtkTextView* text_view;
    GtkImage* image_widget;
    GdkPixbuf* original_pixbuf;
    double current_angle;
};

static void on_button_clicked(GtkWidget* button, gpointer user_data) {
    struct Widgets* widgets = user_data;

    GtkTextBuffer* buffer = gtk_text_view_get_buffer(widgets->text_view);
    GtkTextIter start, end;
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    char* text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    if (g_file_test("Image.bmp", G_FILE_TEST_EXISTS)) {
        if (remove("Image.bmp") != 0) {
            g_print("Impossible de supprimer l'ancien Image.bmp\n");
        }
    }
    g_print("Texte entrer : %s\n", text);
    int i = run_sdl_image(text);
    if (i == 1)
        g_free(text);
    else
   
        gtk_image_set_from_file(widgets->image_widget, "Image.bmp");
        if (widgets->original_pixbuf) {
            g_object_unref(widgets->original_pixbuf);
            widgets->original_pixbuf = NULL;
        }
        
        widgets->current_angle = 0.0;
        g_free(text);
        
}

static void rotate_right(GtkWidget* button, gpointer user_data) {
    struct Widgets* widgets = (struct Widgets*)user_data;
    if (!widgets || !widgets->image_widget) return;

    if (!widgets->original_pixbuf) {
        GError* error = NULL;
        widgets->original_pixbuf = gdk_pixbuf_new_from_file("Image.bmp", &error);
        if (!widgets->original_pixbuf) {
            g_print("Erreur lors du chargement de l'image : %s\n", error->message);
            g_error_free(error);
            return;
        }
        widgets->current_angle = 0.0;
    }

    widgets->current_angle += 10.0;
    double angle_rad = widgets->current_angle * G_PI / 180.0;

    int width = gdk_pixbuf_get_width(widgets->original_pixbuf);
    int height = gdk_pixbuf_get_height(widgets->original_pixbuf);
    int size = (int)ceil(sqrt(width * width + height * height));

    cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, size, size);
    cairo_t* cr = cairo_create(surface);
    cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
    cairo_set_source_rgba(cr, 0, 0, 0, 0);
    cairo_paint(cr);
    cairo_translate(cr, size / 2.0, size / 2.0);
    cairo_rotate(cr, angle_rad);
    cairo_translate(cr, -width / 2.0, -height / 2.0);

    gdk_cairo_set_source_pixbuf(cr, widgets->original_pixbuf, 0, 0);
    cairo_paint(cr);

    GdkPixbuf* rotated = gdk_pixbuf_get_from_surface(surface, 0, 0, size, size);
    gtk_image_set_from_pixbuf(GTK_IMAGE(widgets->image_widget), rotated);
    cairo_destroy(cr);
    cairo_surface_destroy(surface);

    g_print("Rotation cumulée : %.1f° (surface %dx%d)\n", widgets->current_angle, size, size);
}

static void rotate_left(GtkWidget* button, gpointer user_data) {
    struct Widgets* widgets = (struct Widgets*)user_data;
    if (!widgets || !widgets->image_widget) return;

    if (!widgets->original_pixbuf) {
        GError* error = NULL;
        widgets->original_pixbuf = gdk_pixbuf_new_from_file("Image.bmp", &error);
        if (!widgets->original_pixbuf) {
            g_print("Erreur lors du chargement de l'image : %s\n", error->message);
            g_error_free(error);
            return;
        }
        widgets->current_angle = 0.0;
    }
    widgets->current_angle -= 10.0;
    double angle_rad = widgets->current_angle * G_PI / 180.0;
    int width = gdk_pixbuf_get_width(widgets->original_pixbuf);
    int height = gdk_pixbuf_get_height(widgets->original_pixbuf);
    int size = (int)ceil(sqrt(width * width + height * height));

    cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, size, size);
    cairo_t* cr = cairo_create(surface);
    cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
    cairo_set_source_rgba(cr, 0, 0, 0, 0);
    cairo_paint(cr);
    cairo_translate(cr, size / 2.0, size / 2.0);
    cairo_rotate(cr, angle_rad);
    cairo_translate(cr, -width / 2.0, -height / 2.0);

    gdk_cairo_set_source_pixbuf(cr, widgets->original_pixbuf, 0, 0);
    cairo_paint(cr);

    GdkPixbuf* rotated = gdk_pixbuf_get_from_surface(surface, 0, 0, size, size);
    gtk_image_set_from_pixbuf(GTK_IMAGE(widgets->image_widget), rotated);
    cairo_destroy(cr);
    cairo_surface_destroy(surface);

    g_print("Rotation cumulée : %.1f° (surface %dx%d)\n", widgets->current_angle, size, size);
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