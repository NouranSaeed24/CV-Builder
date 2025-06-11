#include <gtk/gtk.h>
#include <string.h>
#include <glib.h>
#include <windows.h>

GtkBuilder *builder;
GtkWidget  *window;
GtkWidget  *stack;

// aboutPage
GtkWidget *nameEntry;
GtkWidget *titleEntry;
GtkWidget *emailEntry;
GtkWidget *phoneEntry;
GtkWidget *locationEntry;
GtkWidget *dobEntry;
GtkWidget *summaryEntry;

// educationPage
GtkWidget *degreeEntry;
GtkWidget *schoolEntry;
GtkWidget *sdEntry;
GtkWidget *edEntry;

// experiencePage
GtkWidget *jobEntry;
GtkWidget *entityEntry;
GtkWidget *dateEntry;
GtkWidget *descriptionEntry;

// skillsPage
GtkWidget *businessSkillsEntry;
GtkWidget *techSkillsEntry;

// languagesPage
GtkWidget *languageEntry;
GtkWidget *comboBoxEntry;

// dataLabels
GtkWidget *dataLabels[4];

// optionBox
GtkWidget *addButton;
GtkWidget *deleteButton;
GtkWidget *generateButton;

FILE *html;
FILE *css;

char itemLabel [600];
int educationCounter=0, experienceCounter=0, languagesCounter=0;

struct about{
   char name[20];
   char title[20];
   char pic[400];
   char email[50];
   char phone[20];
   char location[50];
   char dob[30];
   char summary[250];
}user;

struct education{
  char degree[50];
  char school[50];
  char startDate[20];
  char endDate[20];
}eduArray[4];

struct experience{
  char job[50];
  char entity[50];
  char date[20];
  char description[250];
}expArray[4];

struct skills{
    char business[300];
    char tech[300];
}skill;

struct languages{
  char language[20];
  char comboBox[20];
}langArray[4];


void on_addButton_clicked(){
   if (strcmp(gtk_stack_get_visible_child_name(GTK_STACK(stack)) , "about") == 0){
     g_strlcpy (user.name,     gtk_entry_get_text(GTK_ENTRY(nameEntry)),               sizeof(user.name));
     g_strlcpy (user.title,    gtk_entry_get_text(GTK_ENTRY(titleEntry)),              sizeof(user.title));
     g_strlcpy (user.email,    gtk_entry_get_text(GTK_ENTRY(emailEntry)),              sizeof(user.email));
     g_strlcpy (user.phone,    gtk_entry_get_text(GTK_ENTRY(phoneEntry)),              sizeof(user.phone));
     g_strlcpy (user.location, gtk_entry_get_text(GTK_ENTRY(locationEntry)),           sizeof(user.location));
     g_strlcpy (user.dob,      gtk_entry_get_text(GTK_ENTRY(dobEntry)),                sizeof(user.dob));
     g_strlcpy (user.summary,  gtk_entry_get_text(GTK_ENTRY(summaryEntry)),            sizeof(user.summary));
     sprintf (itemLabel ,
               "Name: %s\nTitle: %s\nEmail: %s\nPhone: %s\nLocation: %s\nDate Of Birth: %s\nProfile Summary: %s",
              user.name, user.title, user.email, user.phone, user.location, user.dob, user.summary);
     gtk_label_set_text (GTK_LABEL(dataLabels[0]), itemLabel);
   }

   else if ((strcmp(gtk_stack_get_visible_child_name(GTK_STACK(stack)) , "education") == 0) && educationCounter < 4){
     g_strlcpy (eduArray[educationCounter].degree ,   gtk_entry_get_text(GTK_ENTRY(degreeEntry)), sizeof(eduArray[educationCounter].degree));
     g_strlcpy (eduArray[educationCounter].school ,   gtk_entry_get_text(GTK_ENTRY(schoolEntry)), sizeof(eduArray[educationCounter].school));
     g_strlcpy (eduArray[educationCounter].startDate, gtk_entry_get_text(GTK_ENTRY(sdEntry)),     sizeof(eduArray[educationCounter].startDate));
     g_strlcpy (eduArray[educationCounter].endDate,   gtk_entry_get_text(GTK_ENTRY(edEntry)),     sizeof(eduArray[educationCounter].endDate));
     sprintf (itemLabel,
               "(%d)\nDegree/Course: %s\nSchool/Collage: %s\nStart Date: %s\nEnd Date: %s",
               educationCounter+1, eduArray[educationCounter].degree, eduArray[educationCounter].school,
               eduArray[educationCounter].startDate, eduArray[educationCounter].endDate);
     gtk_label_set_text(GTK_LABEL(dataLabels[educationCounter]), itemLabel);
     educationCounter ++;
   }

   else if ((strcmp(gtk_stack_get_visible_child_name(GTK_STACK(stack)), "experience") == 0) && experienceCounter < 4){
     g_strlcpy (expArray[experienceCounter].job,         gtk_entry_get_text(GTK_ENTRY(jobEntry)),         sizeof(expArray[experienceCounter].job));
     g_strlcpy (expArray[experienceCounter].entity,      gtk_entry_get_text(GTK_ENTRY(entityEntry)),      sizeof(expArray[experienceCounter].entity));
     g_strlcpy (expArray[experienceCounter].date,        gtk_entry_get_text(GTK_ENTRY(dateEntry)),        sizeof(expArray[experienceCounter].date));
     g_strlcpy (expArray[experienceCounter].description, gtk_entry_get_text(GTK_ENTRY(descriptionEntry)), sizeof(expArray[experienceCounter].description));
     sprintf (itemLabel,
              "(%d)\nJob/Project: %s\nEntity: %s\nStart Date: %s\nDescription: %s",
              experienceCounter+1, expArray[experienceCounter].job, expArray[experienceCounter].entity,
              expArray[experienceCounter].date, expArray[experienceCounter].description);
     gtk_label_set_text (GTK_LABEL(dataLabels[experienceCounter]), itemLabel);
     experienceCounter ++;
   }

   else if (strcmp(gtk_stack_get_visible_child_name(GTK_STACK(stack)), "skills") == 0){
      g_strlcpy (skill.business, gtk_entry_get_text(GTK_ENTRY(businessSkillsEntry)), sizeof(skill.business));
      g_strlcpy (skill.tech,     gtk_entry_get_text(GTK_ENTRY(techSkillsEntry)),     sizeof(skill.tech));
      sprintf (itemLabel, "Business Skills: %s", skill.business);
      gtk_label_set_text (GTK_LABEL(dataLabels[0]), itemLabel);
      sprintf (itemLabel, "Technical Skills: %s", skill.tech);
      gtk_label_set_text (GTK_LABEL(dataLabels[1]), itemLabel);
   }
   else if ((strcmp(gtk_stack_get_visible_child_name(GTK_STACK(stack)), "languages") == 0) && languagesCounter < 4){
     g_strlcpy (langArray[languagesCounter].language, gtk_entry_get_text(GTK_ENTRY(languageEntry)), sizeof(langArray[languagesCounter].language));
     gchar *selected = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBoxEntry));
     if (selected != NULL) {
        g_strlcpy(langArray[languagesCounter].comboBox, selected, sizeof(langArray[languagesCounter].comboBox));
        g_free(selected);
}    else {
        g_strlcpy(langArray[languagesCounter].comboBox, "N/A", sizeof(langArray[languagesCounter].comboBox));
     }
     sprintf (itemLabel, "(%d)\nLanguage: %s\nProficiency: %s",
             languagesCounter+1, langArray[languagesCounter].language, langArray[languagesCounter].comboBox);
     gtk_label_set_text(GTK_LABEL(dataLabels[languagesCounter]), itemLabel);
     languagesCounter ++;
   }
}

void on_deleteButton_clicked(){
    if (strcmp(gtk_stack_get_visible_child_name(GTK_STACK(stack)) , "about") == 0){
        if (strcmp(user.name, "") != 0 || strcmp(user.title, "") != 0 || strcmp(user.email, "") != 0 || strcmp(user.phone, "") != 0 || strcmp(user.location, "") != 0 || strcmp(user.dob, "") != 0 || strcmp(user.summary, "") != 0){
             strcpy (user.name,     "");
             strcpy (user.title,    "");
             strcpy (user.email,    "");
             strcpy (user.phone,    "");
             strcpy (user.location, "");
             strcpy (user.dob,      "");
             strcpy (user.summary,  "");
             gtk_label_set_text (GTK_LABEL(dataLabels[0]), "");
        }
   }

   else if ((strcmp(gtk_stack_get_visible_child_name(GTK_STACK(stack)) , "education") == 0) && educationCounter > 0){
     educationCounter --;
     strcpy (eduArray[educationCounter].degree ,  "");
     strcpy (eduArray[educationCounter].school ,  "");
     strcpy (eduArray[educationCounter].startDate,"");
     strcpy (eduArray[educationCounter].endDate,  "");
     gtk_label_set_text (GTK_LABEL(dataLabels[educationCounter]), "");
   }

   else if ((strcmp(gtk_stack_get_visible_child_name(GTK_STACK(stack)), "experience") == 0) && experienceCounter > 0){
     experienceCounter --;
     strcpy (expArray[experienceCounter].job, "");
     strcpy (expArray[experienceCounter].entity, "");
     strcpy (expArray[experienceCounter].date, "");
     strcpy (expArray[experienceCounter].description, "");
     gtk_label_set_text (GTK_LABEL(dataLabels[experienceCounter]), "");
   }

   else if (strcmp(gtk_stack_get_visible_child_name(GTK_STACK(stack)), "skills") == 0){
      strcpy (skill.business, "");
      strcpy (skill.tech,     "");
      gtk_label_set_text(GTK_LABEL(dataLabels[0]), "");
      gtk_label_set_text(GTK_LABEL(dataLabels[1]), "");
   }
   else if ((strcmp(gtk_stack_get_visible_child_name(GTK_STACK(stack)), "languages") == 0) && languagesCounter > 0){
     languagesCounter --;
     strcpy (langArray[languagesCounter].language, "");
     strcpy (langArray[languagesCounter].comboBox, "");
     gtk_label_set_text (GTK_LABEL(dataLabels[languagesCounter]), "");
   }
}

void on_generateButton_clicked() {
    html = fopen("index.html", "w");
    css = fopen("style.css", "w");

    fprintf(html,
        "<!DOCTYPE html>\n"
        "<html lang=\"en\">\n"
        "<head>\n"
        "  <meta charset=\"UTF-8\">\n"
        "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
        "  <title>%s</title>\n"
        "  <link rel=\"stylesheet\" href=\"style.css\">\n"
        "</head>\n"
        "<body>\n"
        "<div class=\"cv\">\n",

        user.name
    );

    fprintf(html,
        "  <header class=\"header\">\n"
        "    <h1>%s</h1>\n"
        "    <h3>%s</h3>\n"
        "    <p><a href=\"mailto:%s\">%s</a> | %s | %s | %s</p>\n"
        "  </header>\n",
        user.name, user.title, user.email, user.email, user.phone, user.dob, user.location
    );

    fprintf(html,
        "  <section>\n"
        "    <h2>Profile Summary</h2>\n"
        "    <p>%s</p>\n"
        "  </section>\n",
        user.summary
    );

    fprintf(html,
        "  <section>\n"
        "    <h2>Skills</h2>\n"
        "    <h3>Business Skills</h3>\n"
        "    <p>%s</p>\n"
        "    <h3>Technical Skills</h3>\n"
        "    <p>%s</p>\n"
        "  </section>\n",
        skill.business, skill.tech
    );

    fprintf(html,
        "  <section>\n"
        "    <h2>Experience</h2>\n");

    for (int i = 0; i < experienceCounter; i++) {
        fprintf(html,
            "    <div class=\"item\">\n"
            "      <h3>%s</h3>\n"
            "      <p><strong>Entity:</strong> %s</p>\n"
            "      <p><strong>Date:</strong> %s</p>\n"
            "      <p>%s</p>\n"
            "    </div>\n",
            expArray[i].job, expArray[i].entity, expArray[i].date, expArray[i].description
        );
    }

    fprintf(html, "  </section>\n");

    fprintf(html,
        "  <section>\n"
        "    <h2>Education</h2>\n");

    for (int i = 0; i < educationCounter; i++) {
        fprintf(html,
            "    <div class=\"item\">\n"
            "      <h3>%s</h3>\n"
            "      <p><strong>Institution:</strong> %s</p>\n"
            "      <p><strong>Start:</strong> %s - <strong>End:</strong> %s</p>\n"
            "    </div>\n",
            eduArray[i].degree, eduArray[i].school, eduArray[i].startDate, eduArray[i].endDate
        );
    }

    fprintf(html, "  </section>\n");

    fprintf(html,
        "  <section>\n"
        "    <h2>Languages</h2>\n");

    for (int i = 0; i < languagesCounter; i++) {
        fprintf(html,
            "    <div class=\"item\">\n"
            "      <p><strong>%s</strong>: %s</p>\n"
            "    </div>\n",
            langArray[i].language, langArray[i].comboBox
        );
    }

    fprintf(html,
        "  </section>\n"
        "</div>\n"
        "</body>\n"
        "</html>\n");

    fprintf(css,
        "body {\n"
        "  font-family: 'Segoe UI', sans-serif;\n"
        "  background-color: #f9f9f9;\n"
        "  margin: 0;\n"
        "  padding: 0;\n"
        "}\n"
        ".cv {\n"
        "  max-width: 800px;\n"
        "  margin: 30px auto;\n"
        "  background-color: #fff;\n"
        "  padding: 20px 30px;\n"
        "  box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);\n"
        "}\n"
        ".header {\n"
        "  text-align: center;\n"
        "  border-bottom: 1px solid #ccc;\n"
        "  padding-bottom: 10px;\n"
        "  margin-bottom: 20px;\n"
        "}\n"
        "section {\n"
        "  margin-bottom: 30px;\n"
        "}\n"
        "h1 {\n"
        "  font-size: 28px;\n"
        "  margin-bottom: 5px;\n"
        "}\n"
        "h2 {\n"
        "  font-size: 22px;\n"
        "  color: teal;\n"
        "  border-bottom: 2px solid teal;\n"
        "  padding-bottom: 5px;\n"
        "}\n"
        "h3 {\n"
        "  margin-top: 10px;\n"
        "  color: #444;\n"
        "}\n"
        ".item {\n"
        "  margin-top: 10px;\n"
        "  padding: 10px;\n"
        "  background-color: #f3f3f3;\n"
        "  border-radius: 5px;\n"
        "}\n"
        "p {\n"
        "  margin: 5px 0;\n"
        "}\n"
    );

    fclose(html);
    fclose(css);
}


int main(){

  HWND w = GetConsoleWindow();
  ShowWindow (w, SW_HIDE);

  gtk_init(NULL,NULL);

  if (!gtk_init_check(NULL, NULL)) {
    fprintf(stderr, "Failed to initialize GTK.\n");
    return 1;
}

  builder = gtk_builder_new_from_file("design.glade");
  window = GTK_WIDGET(gtk_builder_get_object(builder,"window"));
  stack = GTK_WIDGET(gtk_builder_get_object(builder,"stack"));
  //aboutPage
  nameEntry = GTK_WIDGET(gtk_builder_get_object(builder,"nameEntry"));
  titleEntry = GTK_WIDGET(gtk_builder_get_object(builder,"titleEntry"));
  emailEntry = GTK_WIDGET(gtk_builder_get_object(builder,"emailEntry"));
  phoneEntry = GTK_WIDGET(gtk_builder_get_object(builder,"phoneEntry"));
  locationEntry = GTK_WIDGET(gtk_builder_get_object(builder,"locationEntry"));
  dobEntry = GTK_WIDGET(gtk_builder_get_object(builder,"dobEntry"));
  summaryEntry = GTK_WIDGET(gtk_builder_get_object(builder,"summaryEntry"));
  //educationPage
  degreeEntry = GTK_WIDGET(gtk_builder_get_object(builder,"degreeEntry"));
  schoolEntry = GTK_WIDGET(gtk_builder_get_object(builder,"schoolEntry"));
  sdEntry = GTK_WIDGET(gtk_builder_get_object(builder,"sdEntry"));
  edEntry = GTK_WIDGET(gtk_builder_get_object(builder,"edEntry"));
  // experiencePage
  jobEntry = GTK_WIDGET(gtk_builder_get_object(builder,"jobEntry"));
  entityEntry = GTK_WIDGET(gtk_builder_get_object(builder,"entityEntry"));
  dateEntry = GTK_WIDGET(gtk_builder_get_object(builder,"dateEntry"));
  descriptionEntry = GTK_WIDGET(gtk_builder_get_object(builder,"descriptionEntry"));
  // skillsPage
  businessSkillsEntry = GTK_WIDGET(gtk_builder_get_object(builder,"businessSkillsEntry"));
  techSkillsEntry = GTK_WIDGET(gtk_builder_get_object(builder, "techSkillsEntry"));
  // languagesPage
  languageEntry = GTK_WIDGET(gtk_builder_get_object(builder,"languageEntry"));
  comboBoxEntry = GTK_WIDGET(gtk_builder_get_object(builder,"comboBox"));
  // dataLabels
  dataLabels[0] = GTK_WIDGET(gtk_builder_get_object(builder,"dataLabel1"));
  dataLabels[1] = GTK_WIDGET(gtk_builder_get_object(builder,"dataLabel2"));
  dataLabels[2] = GTK_WIDGET(gtk_builder_get_object(builder,"dataLabel3"));
  dataLabels[3] = GTK_WIDGET(gtk_builder_get_object(builder,"dataLabel4"));
  // optionBox
  addButton = GTK_WIDGET(gtk_builder_get_object(builder, "addButton"));
  deleteButton = GTK_WIDGET(gtk_builder_get_object(builder, "deleteButton"));
  generateButton = GTK_WIDGET(gtk_builder_get_object(builder, "generateButton"));

  g_signal_connect (window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect (addButton, "clicked", G_CALLBACK(on_addButton_clicked), NULL);
  g_signal_connect (deleteButton, "clicked", G_CALLBACK(on_deleteButton_clicked), NULL);
  g_signal_connect (generateButton, "clicked", G_CALLBACK(on_generateButton_clicked), NULL);

  gtk_window_set_icon_from_file(GTK_WINDOW(window), "cv-icon.ico", NULL);
  gtk_window_maximize(GTK_WINDOW(window));
  gtk_widget_show(window);
  gtk_main();

}
