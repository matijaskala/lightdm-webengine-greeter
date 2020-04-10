/*
 * This file is part of WebEngine Greeter
 * Copyright (C) 2019  Matija Skala <mskala@gmx.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <lightdm.h>
#include <QAbstractListModel>
#include <QTimer>
#include "greeter.h"

Greeter::Greeter()
: m_greeter{new QLightDM::Greeter{this}}
, m_power{new QLightDM::PowerInterface{this}}
{
    m_greeter->connectToDaemonSync();
    connect(m_greeter, SIGNAL(authenticationComplete()), SLOT(onAuthenticationComplete()));
    connect(m_greeter, SIGNAL(autologinTimerExpired()), SLOT(onAutologinTimerExpired()));
    connect(m_greeter, SIGNAL(idle()), SLOT(onIdle()));
    connect(m_greeter, SIGNAL(reset()), SLOT(onReset()));
    connect(m_greeter, SIGNAL(showMessage(QString,QLightDM::Greeter::MessageType)), SLOT(onShowMessage(QString,QLightDM::Greeter::MessageType)));
    connect(m_greeter, SIGNAL(showPrompt(QString,QLightDM::Greeter::PromptType)), SLOT(onShowPrompt(QString,QLightDM::Greeter::PromptType)));
    auto username = users().toList().first().toHash()["name"].toString();
    m_shared_data_directory = m_greeter->ensureSharedDataDirSync(username);
    int index = m_shared_data_directory.lastIndexOf('/');
    if (index != -1)
        m_shared_data_directory.chop(m_shared_data_directory.length() - index);
}

QString Greeter::authentication_user() const
{
    return m_greeter->authenticationUser();
}

bool Greeter::autologin_guest() const
{
    return m_greeter->autologinGuestHint();
}

int Greeter::autologin_timeout() const
{
    return m_greeter->autologinTimeoutHint();
}

QString Greeter::autologin_user() const
{
    return m_greeter->autologinUserHint();
}

bool Greeter::can_hibernate() const
{
    return m_power->canHibernate();
}

bool Greeter::can_restart() const
{
    return m_power->canRestart();
}

bool Greeter::can_shutdown() const
{
    return m_power->canShutdown();
}

bool Greeter::can_suspend() const
{
    return m_power->canSuspend();
}

QString Greeter::default_session() const
{
    return m_greeter->defaultSessionHint();
}

bool Greeter::has_guest_account() const
{
    return m_greeter->hasGuestAccountHint();
}

bool Greeter::hide_users_hint() const
{
    return m_greeter->hideUsersHint();
}

QString Greeter::hostname() const
{
    return m_greeter->hostname();
}

bool Greeter::in_authentication() const
{
    return m_greeter->inAuthentication();
}

bool Greeter::is_authenticated() const
{
    return m_greeter->isAuthenticated();
}

QVariant Greeter::language() const
{
    auto lang = lightdm_get_language();
    QVariantHash h;
    h["code"] = lightdm_language_get_code(lang);
    h["name"] = lightdm_language_get_name(lang);
    h["territory"] = lightdm_language_get_territory(lang);
    return h;
}

QVariant Greeter::languages() const
{
    auto langs = lightdm_get_languages();
    QVariantList l;
    for (auto i = g_list_first(langs); i; i = g_list_next(i)) {
        auto lang = static_cast<LightDMLanguage*>(i->data);
        QVariantHash h;
        h["code"] = lightdm_language_get_code(lang);
        h["name"] = lightdm_language_get_name(lang);
        h["territory"] = lightdm_language_get_territory(lang);
        l << h;
    }
    return l;
}

QVariant Greeter::layout() const
{
    auto layout = lightdm_get_layout();
    QVariantHash h;
    h["description"] = lightdm_layout_get_description(layout);
    h["name"] = lightdm_layout_get_name(layout);
    h["short_description"] = lightdm_layout_get_short_description(layout);
    return h;
}

QVariant Greeter::layouts() const
{
    auto layouts = lightdm_get_layouts();
    QVariantList l;
    for (auto i = g_list_first(layouts); i; i = g_list_next(i)) {
        auto layout = static_cast<LightDMLayout*>(i->data);
        QVariantHash h;
        h["description"] = lightdm_layout_get_description(layout);
        h["name"] = lightdm_layout_get_name(layout);
        h["short_description"] = lightdm_layout_get_short_description(layout);
        l << h;
    }
    return l;
}

bool Greeter::lock_hint() const
{
    return m_greeter->lockHint();
}

QVariant Greeter::remote_sessions() const
{
    auto layouts = lightdm_get_sessions();
    QVariantList l;
    for (auto i = g_list_first(layouts); i; i = g_list_next(i)) {
        auto session = static_cast<LightDMSession*>(i->data);
        QVariantHash h;
        h["comment"] = lightdm_session_get_comment(session);
        h["key"] = lightdm_session_get_key(session);
        h["name"] = lightdm_session_get_name(session);
        h["type"] = lightdm_session_get_session_type(session);
        l << h;
    }
    return l;
}

bool Greeter::select_guest_hint() const
{
    return m_greeter->selectGuestHint();
}

QString Greeter::select_user_hint() const
{
    return m_greeter->selectUserHint();
}

QVariant Greeter::sessions() const
{
    auto layouts = lightdm_get_sessions();
    QVariantList l;
    for (auto i = g_list_first(layouts); i; i = g_list_next(i)) {
        auto session = static_cast<LightDMSession*>(i->data);
        QVariantHash h;
        h["comment"] = lightdm_session_get_comment(session);
        h["key"] = lightdm_session_get_key(session);
        h["name"] = lightdm_session_get_name(session);
        h["type"] = lightdm_session_get_session_type(session);
        l << h;
    }
    return l;
}

QString Greeter::shared_data_directory() const
{
    return m_shared_data_directory;
}

bool Greeter::show_manual_login_hint() const
{
    return m_greeter->showManualLoginHint();
}

bool Greeter::show_remote_login_hint() const
{
    return m_greeter->showRemoteLoginHint();
}

QString Greeter::themes_directory() const
{
    return m_themes_directory;
}

QVariant Greeter::users() const
{
    auto layouts = lightdm_user_list_get_users(lightdm_user_list_get_instance());
    QVariantList l;
    for (auto i = g_list_first(layouts); i; i = g_list_next(i)) {
        auto user = static_cast<LightDMUser*>(i->data);
        QVariantHash h;
        h["display_name"] = lightdm_user_get_display_name(user);
        h["home_directory"] = lightdm_user_get_home_directory(user);
        h["image"] = lightdm_user_get_image(user);
        h["language"] = lightdm_user_get_language(user);
        h["layout"] = lightdm_user_get_layout(user);
        h["logged_in"] = lightdm_user_get_logged_in(user);
        h["session"] = lightdm_user_get_session(user);
        h["username"] = lightdm_user_get_name(user);
        l << h;
    }
    return l;
}

void Greeter::authenticate(QString username)
{
    m_greeter->authenticate(username);
}

void Greeter::authenticate_as_guest()
{
    m_greeter->authenticateAsGuest();
}

void Greeter::cancel_authentication()
{
    m_greeter->cancelAuthentication();
}

void Greeter::cancel_autologin()
{
    m_greeter->cancelAutologin();
}

bool Greeter::hibernate()
{
    return m_power->hibernate();
}

void Greeter::respond(QString response)
{
    m_greeter->respond(response);
}

bool Greeter::restart()
{
    return m_power->restart();
}

void Greeter::set_language(QString lang)
{
    if (m_greeter->isAuthenticated())
        m_greeter->setLanguage(lang);
}

bool Greeter::shutdown()
{
    return m_power->shutdown();
}

bool Greeter::start_session(QString session)
{
    if (session.isEmpty())
        return false;
    return m_greeter->startSessionSync(session);
}

bool Greeter::suspend()
{
    return m_power->suspend();
}

#define DELAY 300
void Greeter::onAuthenticationComplete()
{
    emit propertyChanged();
    QTimer::singleShot(DELAY, [this] { emit authentication_complete(); });
}

void Greeter::onAutologinTimerExpired()
{
    emit propertyChanged();
    QTimer::singleShot(DELAY, [this] { emit autologin_timer_expired(); });
}

void Greeter::onIdle()
{
    emit propertyChanged();
    QTimer::singleShot(DELAY, [this] { emit idle(); });
}

void Greeter::onReset()
{
    emit propertyChanged();
    QTimer::singleShot(DELAY, [this] { emit reset(); });
}

void Greeter::onShowMessage ( QString text, QLightDM::Greeter::MessageType type )
{
    emit propertyChanged();
    QTimer::singleShot(DELAY, [this,text,type] { emit show_message(text, type); });
}

void Greeter::onShowPrompt ( QString text, QLightDM::Greeter::PromptType type )
{
    emit propertyChanged();
    QTimer::singleShot(DELAY, [this,text,type] { emit show_prompt(text, type); });
}
