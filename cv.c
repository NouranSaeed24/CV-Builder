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

void on_generateButton_clicked(){
    html = fopen("index.html", "w");
    css = fopen ("style.css", "w");

    fprintf (html, "<html lang=\"en\"> <head> <meta charset=\"utf-8\" /> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" /> <title>%s</title> <link rel=\"stylesheet\" href=\"style.css\" /> </head> <body> <div class=\"cv\"> <div class=\"total\"> <div class=\"header\"> <h1>%s</h1> <h3>%s</h3> </div> <div class=\"details\"> <span class=\"info\"><a title=\"Get in touch\" target=\"_blank\" href=\"mailto:%s\">%s</a></span> <span class=\"separator\">|</span> <span class=\"info\"><a title=\"Call %s\" href=\"tel:%s\">%s</a></span> <span class=\"separator\">|</span> <span class=\"info\">%s</span> <span class=\"separator\">|</span> <span class=\"info\">%s</span> </div> </div> <div class=\"main\"> <!-- PROFILE SUMMARY --> <div class=\"section\"> <div class=\"section-title\"><span>PROFILE SUMMARY</span></div> <p> <div class=\"profile-summary-lines\"> %s <br> </div> </p> </div> <!-- SKILLS --> <div class=\"section\"> <div class=\"section-title\"><span>SKILLS</span></div> <div class=\"skills\"> <div class=\"skill-block\"> <div class=\"skill-title\">BUSINESS SKILLS</div> <div class=\"skill-description\"> %s </div> </div> <div class=\"skill-block\"> <div class=\"skill-title\">TECHNICAL SKILLS</div> <div class=\"skill-description\"> %s </div> </div> </div> </div>",
             user.name, user.name, user.title, user.email, user.email, user.name, user.phone, user.phone, user.dob, user.location, user.summary, skill.business, skill.tech);

    fprintf (html, "<div class=\"section\"> <div class=\"section-title\"><span>EXPERIENCE</span></div> <div class=\"projects\">");

    for (int i=0 ; i < experienceCounter ; i++)
        fprintf (html, "<div class=\"skill-block\"> <div class=\"skill-title\">%s</div> <div class=\"skill-description\"> <strong>Entity:</strong> %s<br /> <strong>Start Date:</strong> %s<br /><br /> %s </div> </div>", expArray[i].job, expArray[i].entity, expArray[i].date, expArray[i].description );

    fprintf (html, "</div> </div> <!-- EDUCATION --> <div class=\"section\"> <div class=\"section-title\"><span>EDUCATION</span></div> <div class=\"education\">");

    for (int i=0 ; i < educationCounter ; i++)
        fprintf (html, "<div class=\"skill-block\"> <div class=\"skill-title\">%s</div> <div class=\"skill-description\"> Institution: %s<br /> Start Date: %s<br /> End Date: %s </div> </div>", eduArray[i].degree, eduArray[i].school, eduArray[i].startDate, eduArray[i].endDate );

    fprintf (html, "</div> </div> <!-- LANGUAGES --> <div class=\"section\"> <div class=\"section-title\"><span>LANGUAGES</span></div>");

    for (int i=0 ; i < languagesCounter ; i++)
        fprintf (html, "<div class=\"skill-block\"> <div class=\"skill-description\"> %s , %s<br /> </div> </div>", langArray[i].language, langArray[i].comboBox );

    fprintf (html, "</div></div></div></body></html>");

    fprintf (css, "@import url('https://fonts.googleapis.com/css2?family=Raleway:ital,wght@0,100..900;1,100..900&display=swap'); body { font-family:\"Raleway\", sans-serif; background-color: #f5f5f5; padding: 20px 0; color: #333; line-height: 1.6; } .cv { display: flex; flex-direction: column; width: 90%; max-width: 900px; margin: auto; background-color: white; box-shadow: 0 0 10px rgba(0,0,0,0.1); padding: 30px; } h1, h2, h3 { color: teal; margin: 0; } h1 { font-size: 28px; text-transform: uppercase; } h3 { font-size: 18px; font-weight: normal; margin-top: 5px; } .total { display: flex; flex-direction: column; align-items: center; background-color: white; padding: 10px; } .header { display: flex; flex-direction: column; align-items: center; background-color: white; margin-bottom: 15px; } .details { display: flex; flex-wrap: wrap; justify-content: center; gap: 10px; text-align: center; padding: 10px 0; font-size: 1rem; line-height: 1.6; color: #333; } .details .info { display: inline-block; margin: 0 10px; white-space: nowrap; } .details .separator { margin: 0 10px; color: #888; } .details a { text-decoration: none; color: teal; font-weight: bold; } .details a:hover { text-decoration: underline; } .main > div { margin: 20px 0; display: flex; flex-direction: column; background-color: white; } .profile-summary-lines { line-height: 1.6; padding: 0 20px; } .skills { padding: 0 20px; } .skill-block { display: grid; grid-template-columns: 200px 1fr; gap: 20px; margin-bottom: 20px; align-items: start; } .skill-title { font-weight: bold; text-transform: uppercase; color: #333; } .skill-description { text-align: justify; color: #444; line-height: 1.6; } .section { margin: 30px 0; } .section-title { display: flex; align-items: center; justify-content: center; margin-bottom: 20px; font-weight: bold; font-size: 22px; color: teal; } .section-title::before, .section-title::after { content: ""; flex: 1; border-bottom: 2px solid teal; margin: 0 12px; } .section-title span { font-size: 24px; color: teal; font-weight: bold; letter-spacing: 1px; } .projects a, .education a { text-decoration: none; color: teal; font-weight: bold; } .projects a:hover, .education a:hover { text-decoration: underline; } ul { padding-left: 20px; margin: 10px 0; } li { margin-bottom: 5px; } @media screen and (max-width: 600px) { .cv { width: 95%; padding: 15px; } .details { flex-direction: column; gap: 5px; font-size: 14px; display: flex; align-items: center; } .details .separator { display: none; } .details .info { margin: 5px 0; } h1 { font-size: 22px; } h3 { font-size: 14px; } .skill-block { grid-template-columns: 1fr; } .section-title span { font-size: 18px; } .skill-title { font-size: 16px; } .skill-description { font-size: 14px; } }");

    fclose (html);
    fclose (css);
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
