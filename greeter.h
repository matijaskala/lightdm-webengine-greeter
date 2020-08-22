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

#ifndef GREETER_H
#define GREETER_H

#include <QObject>
#include <lightdm-qt5-3/QLightDM/greeter.h>
#include <lightdm-qt5-3/QLightDM/power.h>

class Greeter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString authentication_user READ authentication_user NOTIFY propertyChanged)
    Q_PROPERTY(bool autologin_guest READ autologin_guest CONSTANT)
    Q_PROPERTY(int autologin_timeout READ autologin_timeout CONSTANT)
    Q_PROPERTY(QString autologin_user READ autologin_user CONSTANT)
    Q_PROPERTY(bool can_hibernate READ can_hibernate CONSTANT)
    Q_PROPERTY(bool can_restart READ can_restart CONSTANT)
    Q_PROPERTY(bool can_shutdown READ can_shutdown CONSTANT)
    Q_PROPERTY(bool can_suspend READ can_suspend CONSTANT)
    Q_PROPERTY(QString default_session READ default_session CONSTANT)
    Q_PROPERTY(bool has_guest_account READ has_guest_account CONSTANT)
    Q_PROPERTY(bool hide_users_hint READ hide_users_hint CONSTANT)
    Q_PROPERTY(QString hostname READ hostname CONSTANT)
    Q_PROPERTY(bool in_authentication READ in_authentication NOTIFY propertyChanged)
    Q_PROPERTY(bool is_authenticated READ is_authenticated NOTIFY propertyChanged)
    Q_PROPERTY(QVariant language READ language NOTIFY propertyChanged)
    Q_PROPERTY(QVariant languages READ languages CONSTANT)
    Q_PROPERTY(QVariant layout READ layout  NOTIFY propertyChanged)
    Q_PROPERTY(QVariant layouts READ layouts CONSTANT)
    Q_PROPERTY(bool lock_hint READ lock_hint CONSTANT)
    Q_PROPERTY(QVariant remote_sessions READ remote_sessions NOTIFY propertyChanged)
    Q_PROPERTY(bool select_guest_hint READ select_guest_hint CONSTANT)
    Q_PROPERTY(QString select_user_hint READ select_user_hint CONSTANT)
    Q_PROPERTY(QVariant sessions READ sessions CONSTANT)
    Q_PROPERTY(QString shared_data_directory READ shared_data_directory CONSTANT)
    Q_PROPERTY(bool show_manual_login_hint READ show_manual_login_hint CONSTANT)
    Q_PROPERTY(bool show_remote_login_hint READ show_remote_login_hint CONSTANT)
    Q_PROPERTY(QString themes_directory READ themes_directory CONSTANT)
    Q_PROPERTY(QVariant users READ users CONSTANT)

public:
    Greeter();

    QString authentication_user() const;
    bool autologin_guest() const;
    int autologin_timeout() const;
    QString autologin_user() const;
    bool can_hibernate() const;
    bool can_restart() const;
    bool can_shutdown() const;
    bool can_suspend() const;
    QString default_session() const;
    bool has_guest_account() const;
    bool hide_users_hint() const;
    QString hostname() const;
    bool in_authentication() const;
    bool is_authenticated() const;
    QVariant language() const;
    QVariant languages() const;
    QVariant layout() const;
    QVariant layouts() const;
    bool lock_hint() const;
    QVariant remote_sessions() const;
    bool select_guest_hint() const;
    QString select_user_hint() const;
    QVariant sessions() const;
    QString shared_data_directory() const;
    bool show_manual_login_hint() const;
    bool show_remote_login_hint() const;
    QString themes_directory() const;
    QVariant users() const;

public Q_SLOTS:
    void authenticate(QString username);
    void authenticate_as_guest();
    void cancel_authentication();
    void cancel_autologin();
    bool hibernate();
    void respond(QString response);
    bool restart();
    void set_language(QString lang);
    bool shutdown();
    bool start_session(QString session);
    bool suspend();

private Q_SLOTS:
    void onAuthenticationComplete();
    void onAutologinTimerExpired();
    void onIdle();
    void onReset();
    void onShowMessage (QString text, QLightDM::Greeter::MessageType type);
    void onShowPrompt (QString text, QLightDM::Greeter::PromptType type);

Q_SIGNALS:
    void authentication_complete();
    void autologin_timer_expired();
    void idle();
    void reset();
    void show_message(QString text, QString type);
    void show_prompt(QString text, QString type);
    void propertyChanged();

private:
    QLightDM::Greeter* m_greeter;
    QLightDM::PowerInterface* m_power;
    QString m_shared_data_directory;
    QString m_themes_directory = DATADIR "/lightdm-webengine-greeter/themes";
};

#endif // GREETER_H
