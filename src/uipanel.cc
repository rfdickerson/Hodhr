# <cairo.h>
# "include/uipanel.h"
# <include/texture.h>


#define GLM_FORCE_RADIANS
# <glm/gtc/matrix_transform.hpp>
# <glm/gtx/transform.hpp>


namespace Hodhr {

UIPanel::UIPanel(GLuint width, GLuint height)
{
    width_ = width;
    height_ = height;
    createCairoPanel(width, height);
    createQuad();
}

UIPanel::~UIPanel()
{

}


void UIPanel::createCairoPanel(GLuint width, GLuint height)
{

    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    cairo_surface_t *surface;
    cairo_t *cr;
    cairo_pattern_t *pat;
    
    pat = cairo_pattern_create_linear(0.0, 0.0, 0.0, 256.0);
    cairo_pattern_add_color_stop_rgba(pat, 1, 0, 0, 0, 1);
    cairo_pattern_add_color_stop_rgba(pat, 0, 1, 1, 1, 1);

    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cr = cairo_create(surface);

    cairo_set_source_rgb(cr, .2, .2, .2);

    double x         = 25.6,        /* parameters like cairo_rectangle */
           y         = 25.6,
           aspect        = 1.0,     /* aspect ratio */
           corner_radius = height / 10.0;   /* and corner curvature radius */

    double radius = corner_radius / aspect;
    double degrees = M_PI / 180.0;

    cairo_new_sub_path (cr);
    cairo_arc (cr, x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
    cairo_arc (cr, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
    cairo_arc (cr, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
    cairo_arc (cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
    cairo_close_path (cr);

    cairo_set_source(cr, pat);
    // cairo_set_source_rgb (cr, 0.1, 0.1, .1);
    cairo_fill_preserve (cr);
    cairo_set_source_rgba (cr, 0, 0, 0, 0.5);
    cairo_set_line_width (cr, 5.0);
    cairo_stroke (cr);

    // cairo_arc(cr, 0, 0, 50, 0, 2 * M_PI);
    //4cairo_fill(cr);

    unsigned char* data = cairo_image_surface_get_data(surface);

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 width,
                 height,
                 0,
                 GL_BGRA,
                 GL_UNSIGNED_BYTE,
                 data);

    cairo_pattern_destroy(pat);
    cairo_destroy(cr);
    cairo_surface_destroy(surface);


    Texture* texture = new Texture("cairo", texture_id, width, height);

    active_texture_ = texture;

    glm::vec3 Scale = glm::vec3(this->width_/1280.0f, this->height_/720.0f, 1);
    glm::vec3 Position = glm::vec3(0.2f, 0.2f, 0.0f);
    mv_matrix_ = glm::translate(
                     glm::mat4(1.0f),
                     Position);

    mv_matrix_ = glm::scale(
                     mv_matrix_,
                     Scale);
}


}  // namespace Hodhr
