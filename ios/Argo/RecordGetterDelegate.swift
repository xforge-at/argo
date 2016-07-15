//
//  RecordGetterDelegate.swift
//  ArgoApp
//
//  Created by Manu Wallner on 10.07.2016.
//
//

import Foundation

public class RecordGetterDelegate : NSObject, XFMyRecordGetterDelegate {
    public func receiveRecord(record: XFMyRecord) {
        print("Receiving a record from C++...")
        print("ID: \(record.id)")
        for text in record.texts {
            print(text)
        }
        print("Our optional is also: \(record.optionalTest)")
    }
    
    public func shouldGetRecord() -> Bool {
        print("C++ wants to know if we should receive a record")
        return true
    }
}