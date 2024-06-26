﻿/*
 *  Modern Native AddIn
 *  Copyright (C) 2018  Infactum
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include <chrono>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>

#include "SmartCardReaderAddIn.h"
#include "xpcsc.hpp"

std::string SmartCardReaderAddIn::extensionName() {
    return "SmartCardReader";
}

SmartCardReaderAddIn::SmartCardReaderAddIn() {
    // Universal property. Could store any supported by native api type.
    sample_property = std::make_shared<variant_t>();
    AddProperty(L"SampleProperty", L"ОбразецСвойства", sample_property);

    // Full featured property registration example
    AddProperty(L"Version", L"ВерсияКомпоненты", [&]() {
        auto s = std::string(Version);
        return std::make_shared<variant_t>(std::move(s));
    });

    // Method registration.
    // Lambdas as method handlers are not supported.
    AddMethod(L"Add", L"Сложить", this, &SmartCardReaderAddIn::add);
    AddMethod(L"Message", L"Сообщить", this, &SmartCardReaderAddIn::message);
    AddMethod(L"CurrentDate", L"ТекущаяДата", this, &SmartCardReaderAddIn::currentDate);
    AddMethod(L"Assign", L"Присвоить", this, &SmartCardReaderAddIn::assign);
    AddMethod(L"SamplePropertyValue", L"ЗначениеСвойстваОбразца", this, &SmartCardReaderAddIn::samplePropertyValue);

    AddMethod(L"SmartCardTest", L"ТестСмартКарты", this, &SmartCardReaderAddIn::smartCardTest);

    // Method registration with default arguments
    //
    // Notice that if variant_t would be non-copy you can't use initializer list.
    // Proper way to register def args would be then:
    //        std::map<long, variant_t> def_args;
    //        def_args.insert({0, 5});
    //        AddMethod(u"Sleep", u"Ожидать", this, &SmartCardReaderAddIn::sleep, std::move(def_args));
    //
    AddMethod(L"Sleep", L"Ожидать", this, &SmartCardReaderAddIn::sleep, {{0, 5}});

}

// Sample of addition method. Support both integer and string params.
// Every exceptions derived from std::exceptions are handled by components API
variant_t SmartCardReaderAddIn::add(const variant_t &a, const variant_t &b) {
    if (std::holds_alternative<int32_t>(a) && std::holds_alternative<int32_t>(b)) {
        return std::get<int32_t>(a) + std::get<int32_t>(b);
    } else if (std::holds_alternative<std::string>(a) && std::holds_alternative<std::string>(b)) {
        return std::string{std::get<std::string>(a) + std::get<std::string>(b)};
    } else {
        throw std::runtime_error(u8"Неподдерживаемые типы данных");
    }
}

void SmartCardReaderAddIn::message(const variant_t &msg) {
    std::visit(overloaded{
            [&](const std::string &v) { AddError(ADDIN_E_INFO, extensionName(), v, false); },
            [&](const int32_t &v) {
                AddError(ADDIN_E_INFO, extensionName(), std::to_string(static_cast<int>(v)), false);
            },
            [&](const double &v) { AddError(ADDIN_E_INFO, extensionName(), std::to_string(v), false); },
            [&](const bool &v) {
                AddError(ADDIN_E_INFO, extensionName(), std::string(v ? u8"Истина" : u8"Ложь"), false);
            },
            [&](const std::tm &v) {
                std::ostringstream oss;
                oss.imbue(std::locale("ru_RU.utf8"));
                oss << std::put_time(&v, "%c");
                AddError(ADDIN_E_INFO, extensionName(), oss.str(), false);
            },
            [&](const std::vector<char> &v) {},
            [&](const std::monostate &) {}
    }, msg);
}

void SmartCardReaderAddIn::sleep(const variant_t &delay) {
    using namespace std;
    // It safe to get any type from variant.
    // Exceptions are handled by component API.
    this_thread::sleep_for(chrono::seconds(get<int32_t>(delay)));
}

// Out params support option must be enabled for this to work
void SmartCardReaderAddIn::assign(variant_t &out) {
    out = true;
}

void SmartCardReaderAddIn::smartCardTest()
{
    xpcsc::Connection c;
    try {
        c.init();
    }
    catch (xpcsc::PCSCError& e) {
        throw std::runtime_error(std::string(e.what()));
    }

    try {
        auto readers = c.readers();
    }
    catch (xpcsc::PCSCError& e) {
        throw std::runtime_error(std::string(e.what()));
    }

    xpcsc::Reader reader;

    try {
        auto readers = c.readers();
        auto reader_name = *readers.begin();
        reader = c.wait_for_reader_card(reader_name);
    }
    catch (xpcsc::PCSCError& e) {
        throw std::runtime_error(std::string(e.what()));
    }

    LPCSCARD_IO_REQUEST protocol;
    if (reader.send_pci->dwProtocol == 1)
        protocol = SCARD_PCI_T0;
    else
        protocol = SCARD_PCI_T1;

    xpcsc::Bytes command;
    xpcsc::Bytes response;
    uint16_t response_status;

    //	command.assign(xpcsc::parse_apdu("00 A4 00 0C"));  // для выбора MF // выбирать по id, первое или единственное вхождение, нет данных ответа
    command.assign(xpcsc::parse_apdu("00 A4 00 0C 02 3F 00"));  // для выбора MF // выбирать по id, первое или единственное вхождение, нет данных ответа // Для новых УЛ 2023
    c.transmit(reader, command, &response);
    response_status = c.response_status(response);

    if (response_status != 0x9000) {
        //		std::cerr << "Failed to fetch MF: " << c.response_status_str(response) << std::endl;
        throw std::runtime_error(std::string(c.response_status_str(response)));
    }

}

// Despite that you can return property value through method this is not recommended
// due to unwanted data copying
variant_t SmartCardReaderAddIn::samplePropertyValue() {
    return *sample_property;
}

variant_t SmartCardReaderAddIn::currentDate() {
    using namespace std;
    tm current{};
    time_t t = time(nullptr);
#ifdef _WINDOWS
    localtime_s(&current, &t);
#else
    localtime_r(&t, &current);
#endif
    return current;
}
