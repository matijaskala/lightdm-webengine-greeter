password_entered = false;

function show_prompt(text, type)
{
  // type is either "text" or "password"
  if (type == "text") {
    entry = document.getElementById("username_entry");
    text = "Username:";
  }
  if (type == "password")
  {
    entry = document.getElementById("password_entry");
    text = "Password:";
    if (lightdm.authentication_user != null && lightdm.authentication_user.length > 0)
      text = "Password for " + lightdm.authentication_user + ":";
    if (password_entered)
      lightdm.respond(entry.value);
    entry.value = "";
  }
}

/*
 * show_message callback.
 */

function show_message(text, type)
{
  container = document.getElementById(type + "_container");
  if (text.length > 0)
    container.innerHTML = '<div class="alert alert-danger show" role="alert" style="margin: auto; width: 50%"><b>' + text + '</b><button type="button" class="close" data-dismiss="alert" aria-label="Close"><span aria-hidden="true">&times;</span></button></div';
  else
    container.innerHTML = '';
}

/*
 * authentication_complete callback.
 */

function authentication_complete()
{
  if (!password_entered)
    return;
  if (lightdm.is_authenticated)
  {
    if (selected_session == "default")
    {
      if (lightdm.default_session != null && lightdm.default_session.length > 0)
        lightdm.start_session (lightdm.default_session);
    }
    else if (selected_session == "previous")
    {
      for (i in lightdm.users)
        if (lightdm.users[i].username == lightdm.authentication_user)
        {
          if (lightdm.users[i].session != null && lightdm.users[i].session.length > 0)
            lightdm.start_session (lightdm.users[i].session);
          if (lightdm.default_session != null && lightdm.default_session.length > 0)
            lightdm.start_session (lightdm.default_session);
          break;
        }
    }
    else
      lightdm.start_session (selected_session);
  }
  else
  {
    document.body.style.cursor = "initial";
    show_message ("Authentication Failed", "error");
  }
}

/*
 * autologin_timer_expired callback.
 */

function autologin_timer_expired()
{
  /* Stub.  Does nothing. */
}

/*********************************************************************/
/*                Functions local to this greeter                    */
/*********************************************************************/

/*
 * handle the input from the entry field.
 */

function handle_username()
{
  entry = document.getElementById("username_entry");
  document.body.style.cursor = "initial";
  lightdm.authenticate(entry.value);
}

function handle_login()
{
  password_entered = true;
  handle_username();
  document.body.style.cursor = "wait";
  show_message("", "error");
}

function select_user(name)
{
  password_entered = false;
  entry = document.getElementById("username_entry");
  entry.value = name;
  handle_username();
  entry = document.getElementById("password_entry");
  entry.focus();
  var session_name = null;
  for (i in lightdm.users)
    if (lightdm.users[i].username == lightdm.authentication_user)
    {
      session_name = lightdm.users[i].session;
      break;
    }
  if (session_name == null && lightdm.default_session != null && lightdm.default_session.length > 0)
    session_name = lightdm.default_session;
  for (i in lightdm.sessions)
    if (lightdm.sessions[i].key == session_name)
    {
      panels.prev_session.setAttribute("title", "Previous session (" + lightdm.sessions[i].name + ")");
      panels.prev_session.innerHTML = "Previous (" + lightdm.sessions[i].name + ")";
      break;
    }
}

var selected_session = null;
function select_session(name)
{
  if (selected_session != null)
    document.getElementById("session_" + selected_session).removeAttribute("selected");
  selected_session = name;
  document.getElementById("session_" + selected_session).setAttribute("selected", true);
}

var panels = {
  init: function()
  {
    this.session_button = document.getElementById("session-button");
    this.session_button.addEventListener("click", this);
    this.session_panel = document.getElementById("session-panel");
    this.power_button = document.getElementById("power-button");
    this.power_button.addEventListener("click", this);
    this.power_panel = document.getElementById("power-panel");
    this.default_session = document.getElementById("session_default");
    this.prev_session = document.getElementById("session_previous");
    if (lightdm.default_session != null && lightdm.default_session.length > 0)
      this.default_session.innerHTML = "Default (" + lightdm.default_session + ")";
  },

  session_show: function(event)
  {
    if (this.session_panel.getAttribute("open"))
      return;
    this.session_panel.setAttribute("open", true);
    document.addEventListener("click", this);
    event.stopPropagation();
  },

  power_show: function(event)
  {
    if (this.power_panel.getAttribute("open"))
      return;
    this.power_panel.setAttribute("open", true);
    document.addEventListener("click", this);
    event.stopPropagation();
  },

  power_hide: function()
  {
    this.power_panel.removeAttribute("open");
    document.removeEventListener("click", this);
  },

  handleEvent: function(event)
  {
    switch (event.type) {
      case "click":
        if (event.target == this.session_button && !this.session_panel.getAttribute("open")) {
          this.power_hide();
          this.session_show(event);
        }
        else if (event.target == this.power_button && !this.power_panel.getAttribute("open")) {
          this.session_panel.removeAttribute("open");
          document.removeEventListener("click", this);
          this.power_show(event);
        }
        else if (event.currentTarget == document && !this.power_panel.contains(event.target) && !this.power_panel.contains(event.target)) {
          this.session_panel.removeAttribute("open");
          this.power_hide();
        }
        break;
    }
  },
};

function countdown()
{
 node = document.getElementById('countdown_label');
 node.innerHTML = ' in ' + time_remaining + ' seconds';
 if (time_remaining > 0)
   setTimeout('countdown()', 1000);
 time_remaining--;
}
