import { Routes } from '@angular/router';
import { ShowUsersComponent } from './show-users/show-users.component';
import { DeleteUserComponent } from './delete-user/delete-user.component';
import { AddUserComponent } from './add-user/add-user.component';
import { UpdateUserComponent } from './update-user/update-user.component';
import { LoginComponent } from './login/login.component';

export const routes: Routes = [
    {path: '', component: LoginComponent},
    {path: 'users', component:ShowUsersComponent},
    {path: 'deleteUser', component: DeleteUserComponent},
    {path: 'addUser', component: AddUserComponent},
    {path: 'updateUser', component: UpdateUserComponent}
];
