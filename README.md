# assembler
בס"ד
זהו אסמבלר שמתרגם קובץ בשפת אסמבלי לשפת מכונה ולאחמ"כ ממיר את הקובץ לבסיס 32 כשספרות הבסיס הן:

התוכנית כתובה בשפת C ומיעדת להרצה על לינוקס
התוכנית מקבלת קובץ/ קבצים בשפת אסמבלי עם סיומת .as  כארגומנט בשורת הפקודה
ויוצרת באותה תיקיה עד 4 קבצים קובץ .am  שמכיל את התוכן באסמבלי לאחר פרישת המקרואים
קובץ .ob  עם הקובץ בשפת מכונה מומר לבסיס 32
המורכב מ2 עמודות:
עמודה אחת הכתובת בזיכרון ועמודה שניה הקידוד בבסיס 32
במידה וקיימים משתני entry:  קובץ .ent עם תיעוד שלהם 
וכן במידה וקיימים משתני exstern  קובץ .ext עם תיעוד שלהם.
